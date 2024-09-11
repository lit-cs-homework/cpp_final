
#include "../../include/terminal.h"
#include <stdexcept>
#include <string>
#include <limits>

#include <cstdint>
#include <cstring>
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


PTerminal newTerminal() {
    auto result = std::make_shared<Terminal>();
    initTerminal(result);
    return result;
}

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

NI16 defaultForegroundColor = 0xFFFF;
NI16 defaultBackgroundColor = 0xFFFF;


#define genSetColor(cls, defval, BF) \
_PRE \
void set##cls##Color(FILE* f, cls##Color bg ,bool bright)\
{\
    auto h = conHandle(f);\
    auto old = getAttributes(h) & ~ BF##_RGB;\
    if (default##cls##Color == 0xFFFF){\
        default##cls##Color = old;\
        if (bright)\
            old |= BF##_INTENSITY;\
        else\
            old &= ~(BF##_INTENSITY);\
    }\
    const NI lookup[10] = {\
    0, \
    (BF##_RED),\
    (BF##_GREEN),\
    (BF##_RED | BF##_GREEN),\
    (BF##_BLUE),\
    (BF##_RED | BF##_BLUE),\
    (BF##_BLUE | BF##_GREEN),\
    (BF##_BLUE | BF##_GREEN | BF##_RED),0,0};\
    if (bg == defval)\
        SetConsoleTextAttribute(h, NI16(NU16(old) | NU16(default##cls##Color))); \
    else\
        SetConsoleTextAttribute(h, NI16(NU16(old) | NU16(lookup[bg])));\
}

genSetColor(Background, bgDefault, BACKGROUND)
genSetColor(Foreground, fgDefault, FOREGROUND)

#undef genSetColor



#define contains(style, e)  (std::find(style.begin(), style.end(), e) != style.end())

_PRE
void setStyle(FILE* f, StyleSet style ){
    auto h = conHandle(f);
    auto old = getAttributes(h) & (FOREGROUND_RGB | BACKGROUND_RGB);
    auto a = 0;
    if (contains(style,styleBright)) a = a | NI16(FOREGROUND_INTENSITY);
    if (contains(style,styleBlink)) a = a | NI16(BACKGROUND_INTENSITY);
    if (contains(style,styleReverse)) a = a | 0x4000;
    if (contains(style,styleUnderscore)) a = a | 0x8000;
    SetConsoleTextAttribute(h, old | a);

}

#undef contains

_PRE
void resetAttributes(FILE* f){
    auto term = getTerminal();
    if(f == stderr)
        SetConsoleTextAttribute(term->hStderr, term->oldStderrAttr);
    else
        SetConsoleTextAttribute(term->hStdout, term->oldStdoutAttr);
}


static
void setCursorVisibility(FILE* f,bool visible)
{
    CONSOLE_CURSOR_INFO ccsi = {};
    auto h = conHandle(f);
    if (GetConsoleCursorInfo(h, &ccsi) == 0)
      raiseOSError(osLastError());
    ccsi.bVisible = int(visible);
    if (SetConsoleCursorInfo(h, &ccsi) == 0)
      raiseOSError(osLastError());
}

_PRE
void showCursor(FILE* f)
{
    setCursorVisibility(f, true);
}

_PRE
void hideCursor(FILE* f)
{
    setCursorVisibility(f, false);
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
	mode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	mode.c_oflag &= ~OPOST;
	mode.c_cflag  = (mode.c_cflag & ~(CSIZE | PARENB)) | CS8;
	mode.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	mode.c_cc[VMIN] = 1;
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
static CCStr getPos = "\033[6n";
static CCStr ansiResetCode = "\033[0m";


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
inline
bool isascii0_9(char ch) {
    return '0' <= ch && ch <= '9';
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
        else if ( isascii0_9(ch) ){
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
  sprintf(res, "%s%zdm", stylePrefix, style);
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
