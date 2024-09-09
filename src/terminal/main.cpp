
#include "../../include/terminal.h"
#include <cstdint>
#include <stdexcept>
#include <cstring>
#include <string>

#include <cstdio>
#include <cassert>

#define _PRE extern "C" 
typedef size_t NU;

void ntermInit(bool enableTrueColor/*=true*/){
  // TODO
}


_PRE
void eraseScreen(FILE* f)
{ 
  #ifdef _WIN32
    system("cls");
    setCursorXPos(f, 0);
  #else
    fputs("\033[2J", f);
  #endif
}


#ifdef _WIN32


#include <windows.h>
#include <memory>
#include <algorithm>


#include <conio.h>


const NI FOREGROUND_RGB = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const NI BACKGROUND_RGB = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

struct Terminal
{
    bool trueColorIsSupported; 
    bool trueColorIsEnabled;
    bool fgSetColor;
    #ifdef _WIN32
      HANDLE hStdout;
      HANDLE hStderr;
      NI16 oldStdoutAttr;
      NI16 oldStderrAttr;
    #endif
};

using PTerminal = std::shared_ptr<Terminal>;

#define osLastError() GetLastError()

class OSError: public std::exception {
    public:
    int err;
};

static void raiseOSError(DWORD e) {
    OSError err;
    err.err = e;
    throw err;
}

static
void setCursorPos(HANDLE h_p0, NI x_p1, NI y_p2){
    COORD c;
	c.X = ((NI16) (x_p1));
	c.Y = ((NI16) (y_p2));
	NI32 T3_ = SetConsoleCursorPosition(h_p0, c);
}

static
HANDLE conHandle(FILE* f);

_PRE
void setCursorPos(FILE* f, NI x, NI y) {
    setCursorPos(conHandle(f), x, y);
}

// Sets the terminal's cursor to the x position.
// The y position is not changed.
_PRE
void setCursorXPos(FILE* f, NI x){
    auto h = conHandle(f);
    CONSOLE_SCREEN_BUFFER_INFO scrbuf = {};
    if (GetConsoleScreenBufferInfo(h, &scrbuf) == 0)
      raiseOSError(osLastError());
    auto origin = scrbuf.dwCursorPosition;
    origin.X = NI16(x);
    if (SetConsoleCursorPosition(h, origin) == 0)
      raiseOSError(osLastError());
}

static
void getCursorPos(FILE* f,NI& x,NI& y){
    CONSOLE_SCREEN_BUFFER_INFO c ={};
    if (GetConsoleScreenBufferInfo(f, &c) == 0)
        raiseOSError(osLastError());
    x = NI(c.dwCursorPosition.X);
    y = NI(c.dwCursorPosition.Y);
}

_PRE
void getCursorPos(NI& x,NI& y){
    getCursorPos(stdout, x, y);
}

static
NI16 getAttributes(HANDLE h){
    CONSOLE_SCREEN_BUFFER_INFO c = {};
    if (GetConsoleScreenBufferInfo(h, &c) != 0)
      return c.wAttributes;
    return 0x70;
}



static
void initTerminal(PTerminal term){
    auto hStdoutTemp = GetStdHandle(STD_OUTPUT_HANDLE);
    if(DuplicateHandle(GetCurrentProcess(), hStdoutTemp, GetCurrentProcess(),&term->hStdout, 0, 1, DUPLICATE_SAME_ACCESS) == 0)
    {
        raiseOSError(osLastError());
    }
    auto hStderrTemp = GetStdHandle(STD_ERROR_HANDLE);
    if(DuplicateHandle(GetCurrentProcess(), hStderrTemp, GetCurrentProcess(),&term->hStderr, 0, 1, DUPLICATE_SAME_ACCESS) == 0)
      {
        raiseOSError(osLastError());
      }
    term->oldStdoutAttr = getAttributes(term->hStdout);
    term->oldStderrAttr = getAttributes(term->hStderr);
}


// typedef Terminal;

#ifdef _WIN32
    PTerminal newTerminal() {
        auto result = std::make_shared<Terminal>();
        initTerminal(result);
        return result;
    }
#else
  proc newTerminal(): owned(PTerminal) {.gcsafe, raises: [].}
#endif

static
thread_local PTerminal gTerm;

static
PTerminal getTerminal(){
    if (gTerm == nullptr){
    gTerm = newTerminal();
    }
    auto result = gTerm;
    return result; 
}

static
HANDLE conHandle(FILE* f) {
    auto term = getTerminal();
    if(f == stderr) return term->hStderr;
    else return term->hStdout;
}

#ifdef _WIN32
  NI16 defaultForegroundColor = 0xFFFF;
  NI16 defaultBackgroundColor = 0xFFFF;
#endif


#define setColor(cls, defval) \
_PRE \
void set##cls##Color(FILE* f, cls##Color bg ,bool bright)\
{\
    auto h = conHandle(f);\
    auto old = getAttributes(h) & ~ BACKGROUND_RGB;\
    if (default##cls##Color == 0xFFFF){\
        default##cls##Color = old;\
        if (bright)\
        {\
            old = old | BACKGROUND_INTENSITY;\
        } \
        else\
        {\
            old = old & ~(BACKGROUND_INTENSITY);\
        } \
    }\
    const NI lookup[10] = {\
    0, \
    (BACKGROUND_RED),\
    (BACKGROUND_GREEN),\
    (BACKGROUND_RED | BACKGROUND_GREEN),\
    (BACKGROUND_BLUE),\
    (BACKGROUND_RED | BACKGROUND_BLUE),\
    (BACKGROUND_BLUE | BACKGROUND_GREEN),\
    (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED),0,0};\
    if (bg == defval)\
    {\
        SetConsoleTextAttribute(h, NI16(NU16(old) | NU16(default##cls##Color))); \
    }\
    else\
    {\
        SetConsoleTextAttribute(h, NI16(NU16(old) | NU16(lookup[bg])));\
    }\
}

setColor(Background, bgDefault)
setColor(Foreground, fgDefault)



#define contains(style, e)  (std::find(style.begin(), style.end(), e) != style.end())



_PRE
void setStyle(FILE* f, StyleSet style ){
    #ifdef _WIN32
        auto h = conHandle(f);
        auto old = getAttributes(h) & (FOREGROUND_RGB | BACKGROUND_RGB);
        auto a = 0;
        if (contains(style,styleBright)) a = a | NI16(FOREGROUND_INTENSITY);
        if (contains(style,styleBlink)) a = a | NI16(BACKGROUND_INTENSITY);
        if (contains(style,styleReverse)) a = a | 0x4000;
        if (contains(style,styleUnderscore)) a = a | 0x8000;
        SetConsoleTextAttribute(h, old | a);
    #else
        for s in items(style):
        f.write(ansiStyleCode(s))
    #endif
}


_PRE
void resetAttributes(FILE* f){
    #ifdef _WIN32
        auto term = getTerminal();
        if(f == stderr)
            SetConsoleTextAttribute(term->hStderr, term->oldStderrAttr);
        else
            SetConsoleTextAttribute(term->hStdout, term->oldStdoutAttr);
    #else
        f.write(ansiResetCode)
        gFG = 0
        gBG = 0
    #endif
}



#ifdef _WIN32
_PRE
void setCursorVisibility(FILE* f,bool visible)
{
    CONSOLE_CURSOR_INFO ccsi = {};
    auto h = conHandle(f);
    if (GetConsoleCursorInfo(h, &ccsi) == 0)
      raiseOSError(osLastError());
    if (visible){
        ccsi.bVisible = 1;
    }
    else{
        ccsi.bVisible = 0 ;
    } 
    if (SetConsoleCursorInfo(h, &ccsi) == 0)
      raiseOSError(osLastError());
}
#endif

_PRE
void showCursor(FILE* f)
{
    #ifdef _WIN32
        setCursorVisibility(f, true);
    #else
        f.write("\e[?25h") 
    #endif
}

_PRE
void hideCursor(FILE* f)
{
    #ifdef _WIN32
        setCursorVisibility(f, false);
    #else
        f.write("\e[?25h") 
    #endif
}




#else
#include <sys/ioctl.h> // ioctl
//#include <asm/termbits.h>  /* Definition of TIOC*WINSZ constants */
#include <termios.h>
#include <fcntl.h> // open
#include <unistd.h> // close

static void raiseIndexError2(int i, int a) {
    throw std::invalid_argument("index error ");
}

static
void
setRaw(int fd_p0, int time_p1 = TCSAFLUSH) {
	struct termios mode = {};
	auto T1_ = tcgetattr(fd_p0, &mode);
	mode.c_iflag = (NU32)(mode.c_iflag & (NU32)((NU32) ~((NU32)((NU32)((NU32)((NU32)(BRKINT | ICRNL) | INPCK) | ISTRIP) | IXON))));
	mode.c_oflag = (NU32)(mode.c_oflag & (NU32)((NU32) ~(OPOST)));
	mode.c_cflag = (NU32)((NU32)(mode.c_cflag & (NU32)((NU32) ~((NU32)(CSIZE | PARENB)))) | CS8);
	mode.c_lflag = (NU32)(mode.c_lflag & (NU32)((NU32) ~((NU32)((NU32)((NU32)(ECHO | ICANON) | IEXTEN) | ISIG))));
	if ((NU)(VMIN) > (NU)(31)){ raiseIndexError2(VMIN, 31); 	}
	mode.c_cc[VMIN] = 1;
	if ((NU)(VTIME) > (NU)(31)){ raiseIndexError2(VTIME, 31); 	}
	mode.c_cc[VTIME] = 0;
	auto T2_ = tcsetattr(fd_p0, time_p1, &mode);

}

_PRE
char getch() {
	char result = 0;
	struct termios oldMode = {};
	int fd = fileno(stdin);

	auto T2_ = tcgetattr(fd, &oldMode);

	setRaw(fd, TCSAFLUSH);
	result = fgetc(stdin);
	auto T3_ = tcsetattr(fd, TCSADRAIN, &oldMode);
	return result;
}



typedef const char* const  CCStr;
static CCStr stylePrefix = "\033[";
static CCStr getPos = "\e[6n";
static CCStr ansiResetCode = "\e[0m";


// Returns cursor position (x, y)
// writes to stdout and expects the terminal to respond via stdin

class ValueError: public std::invalid_argument {
public:
    ValueError(CCStr msg): std::invalid_argument(msg){};
    ValueError(const std::string msg): std::invalid_argument(msg){};
};

template <typename T>
static void raiseValueError(T s) {
  throw ValueError(s);
}

static
void getCursorPos(FILE* f, NI& x, NI& y) {

    std::string
      xStr,
      yStr;
    char ch{};
    NI ct{};
    bool readX = false;

    // use raw mode to ask terminal for cursor position
    auto fd = fileno(stdin);
    struct termios oldMode = {};
    tcgetattr(fd, &oldMode);
    setRaw(fd);
    fputs(getPos, f);
    fflush(stdout);

    std::string err;
    {
      // parse response format: [yyy;xxxR
      while (true){
        const auto n = fread(&ch, 1, 1, stdin);
        if (n == 0 or ch == 'R') {
          if (xStr == "" || yStr == "") {
            err = "Got character position message that was missing data";
          }
          break;
        }
        ct += 1;
        if (ct > 16)
          err = "Got unterminated character position message from terminal";
        if (ch == ';')
          readX = true;
        else if ('0' <= ch && ch <= '9'){
          if (readX)
            xStr += ch;
          else
            yStr += ch;
        }
      }
    }
    // restore previous terminal mode
    tcsetattr(fd, TCSADRAIN, &oldMode);
    if (!err.empty())
      raiseValueError(err);

    x = std::stoi(xStr);
    y = std::stoi(yStr);

}

_PRE
void getCursorPos(NI& x, NI& y) {
  getCursorPos(stdout, x, y);
}

_PRE
void setCursorPos(FILE* f, NI x, NI y) {
    fprintf(f, "%s%zd%zdf", stylePrefix, y+1, x+1);
}

#ifndef _WIN32
    thread_local int gFG;
    thread_local int gBG;
#endif


_PRE
void setCursorXPos(FILE* f, NI x){
    fprintf(f, "%s%zdG", stylePrefix, x+1);
}

// std::string ansiStyleCode(NI style) {
//   std::string res;
//   res += stylePrefix;
//   res += std::to_string(style);
//   res += 'm';
//   return res; // f"{stylePrefix}{style}m";
// }
_PRE
CCStr ansiStyleCode(NI style) {
  static char res[10]; // style shall not be more than 6 length
  sprintf(res, "%s%dm", stylePrefix, style);
  return res; // f"{stylePrefix}{style}m";
}


_PRE
void setBackgroundColor(FILE* f, BackgroundColor bg, bool bright/*=true*/) {
    gBG = NI(bg);
    if (bright) gBG += 60;
    fputs(ansiStyleCode(gBG), f);
}

_PRE
void setForegroundColor(FILE* f, ForegroundColor fg, bool bright/*=true*/) {
    gFG = NI(fg);
    if (bright) gFG += 60;
    fputs(ansiStyleCode(gFG), f);
}

_PRE
void setStyle(FILE* f, StyleSet style) {
    for (const auto& s: style)
      fputs(ansiStyleCode(s), f);
}


_PRE
void resetAttributes(FILE* f) {
    fputs(ansiResetCode, f);
    gFG = 0;
    gBG = 0;
}


_PRE
void showCursor(FILE* f) {
    fputs("\033[?25h", f);
}

_PRE
void hideCursor(FILE* f) {
    fputs("\033[?251h", f);
}


struct IOctl_WinSize{
  short ws_row, ws_col, ws_xpixel, ws_ypixel;
};


static
NI parseSaturatedNatural(CCStr s, NI& b) {
    NI i {};
    const NI hi = std::numeric_limits<NI>::max();

    if (s[i] == '+') i++;
    if (isascii0_9(s[i])) {
        b = 0;
        while ( isascii0_9(s[i]) ) {
            const auto c = int(s[i]) - '0';
            if ( b<= (hi - c) / 10)
                b = b * 10 + c;
            else
                b = hi;
            i++;
            while ( s[i] == '_' ) i++;
        }
        return i;
    }
    return 0;
}

// Returns terminal width from first fd that supports the ioctl.


#define terminalWH(wh, attr, VAR, DEF) \
static \
NI terminal##wh##Ioctl(std::vector<NI> fds) {\
    IOctl_WinSize win;\
    for (const auto fd: fds)\
      if (ioctl(int(fd), TIOCGWINSZ, &win) != -1)\
        return NI(win.attr);\
    return 0;\
}\
_PRE \
NI terminal##wh() {\
    NI w{};\
    auto s = getenv(VAR);  /*Try standard env var*/ \
    if (strlen(s) > 0 && parseSaturatedNatural(s, w) > 0 && w > 0)\
      return w;\
    w = terminal##wh##Ioctl({0, 1, 2});  /* Try standard file descriptors*/\
    if (w > 0) return w;\
    auto cterm = new char[L_ctermid];  /*Try controlling tty*/\
    auto fd = open(ctermid(cterm), O_RDONLY);\
    if (fd != -1)\
      w = terminal##wh##Ioctl({fd});\
    close(fd);\
    delete[] cterm;\
    if (w > 0) return w;\
    return DEF;  /* Finally default to venerable value*/\
}

terminalWH(Width , ws_col, "COLUMNS", 80);
terminalWH(Height, ws_row, "LINES",   0);

#endif
