/**

A C++ port from Nim 2.1.9's std/terminal

(doc: https://nim-lang.org/docs/terminal.html)

see ./LICENSE for License.
*/



#ifndef _NIM_TERMINAL_H
#define _NIM_TERMINAL_H

#define _PRE extern "C" 

_PRE
const char*
nterm_getVersion(void);

namespace nterm{
  const char* getVersion();
}


#include <cstdint>

#define _NIN(n) typedef int##n##_t NI##n; typedef uint##n##_t NU##n;
_NIN(64)
_NIN(32)
_NIN(16)
_NIN(8)

#undef _NIN

#ifndef NI
#ifndef INTPTR_MAX
# error "please manually define NI (signed integer that has the same size of (void*) ) as your compiler lacks one"
#endif

typedef intptr_t NI;
#endif

#include <cstdio>


#define _VV(sym) _PRE void sym(void);
_VV( enableTrueColors )
_VV( disableTrueColors )
#undef _VV

#define _BV(sym) _PRE bool sym(void);
_BV( isTrueColorSupported )
#undef _BV

void ntermInit(bool enableTrueColor=false);

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
  void sym(NI x, NI y);

_NFII( setCursorPos )

#undef _NFII

#define _FI(sym) _PRE void sym(FILE*, NI);
#define _NFI(sym) _FI(sym)\
  void sym(NI n);

_NFI( setCursorXPos )
//_NFI( setCursorYPos ) // only support in windows


_NFI( cursorUp )
_NFI( cursorDown )

_NFI( cursorForward )
_NFI( cursorBackward )


#define _F(sym) _PRE void sym(FILE* _file=stdout);

_F( eraseLine )
_F( eraseScreen )
_F( resetAttributes )

_F( hideCursor )
_F( showCursor )

#undef _F


_NFI( setBackgroundColorRGB )
_NFI( setForegroundColorRGB )

#undef _FI
#undef _NFI

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
  void sym(en _color, bool bright=false);

_FBcB( setBackgroundColor, BackgroundColor )
_FBcB( setForegroundColor, ForegroundColor )

#undef _FBcB


namespace ncolor{
typedef NI NColor; // nim std/colors.Color; shall be distinct NI,
  // but C++ has not such notion.

_PRE NColor ntermC_rgb(int r, int g, int b);
_PRE NColor ntermC_parseColor(const char* name);

class Base{
    NColor data;
public:
    // for hex notation.
    Base(int rgb);
    Base(int r, int g, int b);
    // @throw `std::invalid_argument`
    Base(const char* name);
    NI toNInt() const;
};

#define DerivedInits(cls) \
    public:\
      cls(int rgb);\
      cls(int r, int g, int b);\
      cls(const char* name);

/* trick: this is shortly-named asumming:
  this is only used via namespace and within `styledWrite`,
  e.g.
```cpp
styledWrite(ncolor::bg(0x12, 0x23, 0x34), "asd");
```
  where the notation is alreadly long enough,
  so other name like `Backgound` is annoying.
*/
class bg: public Base{DerivedInits(bg)};
class fg: public Base{DerivedInits(fg)};
/* do not use a macro that declared class, as that'll
 nullify static-check tools and they will complain there're no
 `bg`, `fg` in this namespace.
 */

#undef DerivedInits

} // namespace

#define _genColor(fun) \
void fun(FILE*f, ncolor::Base c);\
void fun(ncolor::Base c);\
void fun(int r, int g, int b);
//end_define

_genColor( setBackgroundColor )
_genColor( setForegroundColor )

#undef _genColor

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
//void setStyle(FILE* f, Style s){setStyle(f, StyleSet{s});}

#define DefStyles {styleBright}

_PRE void writeStyled(
  const char* s,
  const StyleSet& styles = DefStyles);


#define _genAttr(T, fun) \
void setConsoleAttr(FILE*f, T c);

_genAttr( BackgroundColor, setBackgroundColor )
_genAttr( ncolor::bg, setBackgroundColor )
_genAttr( ForegroundColor, setForegroundColor )
_genAttr( ncolor::fg, setForegroundColor )
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
void styledWriteLine(const char* s);
void styledWriteLine(auto st, auto...args){
  setConsoleAttr(f, st);
  styledWriteLine(args...);
}
#endif // c++20

#undef f

#undef _PRE

#endif  // _NIM_TREMINAL_H
