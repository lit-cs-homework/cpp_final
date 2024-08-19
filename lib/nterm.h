

#ifndef _NIM_TERMINAL_H
#define _NIM_TERMINAL_H

#include <cstdint>
void NimMain(void);
#define ntermInit() NimMain()

#define _NIN(n) typedef int##n##_t NI##n; typedef uint##n##_t NU##n;
_NIN(64)
_NIN(32)
_NIN(16)
_NIN(8)

#undef _NIN

//typedef void* POINTER;
//constexpr int NIM_INTBITS = (8 * sizeof(POINTER));
//#define NIM_INTBITS (8 * sizeof(POINTER))
//static_assert(NIM_INTBITS==64);


//#  if NIM_INTBITS == 64
#include <cstdint>
#if INTPTR_MAX == 9223372036854775807L
typedef NI64 NI;
typedef NU64 NU;
#elif INTPTR_MAX == 2147483647
typedef NI32 NI;
typedef NU32 NU;
#elif INTPTR_MAX == 32767
typedef NI16 NI;
typedef NU16 NU;
#elif INTPTR_MAX == 127
typedef NI8 NI;
typedef NU8 NU;
#else
# error "invalid bit width for int"
#endif

#include <cstdio>

#define _PRE extern "C" 

_PRE char getch(void);

#define _RI(sym) _PRE NI sym(void);

_RI( terminalWidth )
_RI( terminalHeight )

#undef _RI

#define _VIVI(sym) _PRE void sym(NI&, NI&);

_VIVI( getCursorPos )

#undef _VIVI

#define _FII(sym) _PRE void sym(FILE*, NI, NI);
#define _NFII(sym) _FII(sym)\
  void sym(NI x, NI y){sym(stdout, x, y);}

_NFII( setCursorPos )

#undef _NFII

#define _FI(sym) _PRE void sym(FILE*, NI);
#define _NFI(sym) _FI(sym)\
  void sym(NI n){sym(stdout, n);}

_NFI( setCursorXPos )
//_NFI( setCursorYPos ) // only support in windows


_NFI( cursorUp )
_NFI( cursorDown )

_NFI( cursorForward )
_NFI( cursorBackward )

#undef _NFI

#define _F(sym) _PRE void sym(FILE* _file=stdout);

_F( eraseLine )
_F( eraseScreen )
_F( resetAttributes )

_F( hideCursor )
_F( showCursor )

#undef _F


#define _VV(sym) _PRE void sym(void);

_VV( enableTrueColors )
_VV( disableTrueColors )

#undef _VV

#define _BV(sym) _PRE bool sym(void);
_BV( isTrueColorSupported )

_FI( setBackgroundColorRGB )
_FI( setForegroundColorRGB )

#undef _FI
#undef _BV

enum
  ForegroundColor{ // Terminal's foreground colors.
    fgBlack = 30,         // black
    fgRed,                // red
    fgGreen,              // green
    fgYellow,             // yellow
    fgBlue,               // blue
    fgMagenta,            // magenta
    fgCyan,               // cyan
    fgWhite,              // white
    fg8Bit,               // 256-color (not supported, see `enableTrueColors` instead.)
    fgDefault             // default terminal foreground color
  };

enum
  BackgroundColor{
    bgBlack = 40,             // black
    bgRed,                    // red
    bgGreen,                  // green
    bgYellow,                 // yellow
    bgBlue,                   // blue
    bgMagenta,                // magenta
    bgCyan,                   // cyan
    bgWhite,                  // white
    bg8Bit,                   // 256-color (not supported, see `enableTrueColors` instead.)
    bgDefault                 // default terminal background color
  };

#define _FBcB(sym, en) _PRE void sym(FILE* _file, en _color, bool bright=false);\
  void sym(en _color, bool bright=false){sym(stdout, _color, bright);}

_FBcB( setBackgroundColor, BackgroundColor )
_FBcB( setForegroundColor, ForegroundColor )

#undef _FBcB

enum
 Style{
  styleBright = 1,          // bright text
  styleDim,                 // dim text
  styleItalic,              // italic (or reverse on terminals not supporting)
  styleUnderscore,          // underscored text
  styleBlink,               // blinking/bold text
  styleBlinkRapid,          // rapid blinking/bold text (not widely supported)
  styleReverse,             // reverse the background and foreground color
  styleHidden,              // hidden text
  styleStrikethrough        // strikethrough (a delete line)
 };


#include <vector>
typedef std::vector<Style> StyleSet;

_PRE void setStyle(FILE*, StyleSet);
void setStyle(FILE* f, Style s){setStyle(f, StyleSet{s});}

#define DefStyles {styleBright}

_PRE void writeStyled(
  const char* s,
  const StyleSet& styles = DefStyles);


#define _genAttr(T, fun) \
void setConsoleAttr(FILE*f, T c){fun(f, c);}

_genAttr( BackgroundColor, setBackgroundColor )
_genAttr( ForegroundColor, setForegroundColor )
_genAttr( StyleSet, setStyle )
_genAttr( Style, setStyle )
#undef _genAttr

template <typename T>
void styledWrite(FILE* f, T st, const char* s) {
    setConsoleAttr(f, st);
    fputs(s, f);
    resetAttributes(f);
}
template <typename T>
void styledWrite(T c, const char* s) {
  styledWrite(stdout, c, s);}

// XXX: due to C++'s lack of concept before C++23
// we just cannot implement with the first parameter
// as `FILE*`
#define f stdout
template <typename A, typename B>
void styledWrite(A fc, B bc, const char* s) {
    setConsoleAttr(f, bc);
    setConsoleAttr(f, fc);
    fputs(s, f); resetAttributes(f);
}

template <typename A, typename B, typename C>
void styledWrite(A a, B b, C c, const char* s) {
    setConsoleAttr(f, a);
    setConsoleAttr(f, b);
    setConsoleAttr(f, c);
    fputs(s, f); resetAttributes(f);
}

#if __cplusplus < 202000L
#define styledWriteLine(...) do{styledWrite(__VA_ARGS__); putc('\n', stdout);\
  }while(0)
#else
// use of ‘auto’ in parameter declaration only available with
// ‘-std=c++20’ or ‘-fconcepts'
void styledWriteLine(const char* s){
    fputs(s, f);
    resetAttributes(f);
    putc('\n', f);
}
void styledWriteLine(auto st, auto...args){
  setConsoleAttr(f, st);
  styledWriteLine(args...);
}
#endif // c++20

#undef f

#undef _PRE

#endif  // _NIM_TREMINAL_H
