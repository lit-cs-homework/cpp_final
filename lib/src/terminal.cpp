/*in addition to nterm.nim*/
#include "../nterm.h"
#include <cstdio>

// const char* nterm::getVersion(){return nterm_getVersion();}


#include <stdexcept>
#include <cstdlib>
// void NimMain(void);
// // a must before calling any other functions of `nterm`.
// // otherwise a crash may occur.
// void ntermInit(bool enableTrueColor/*=true*/){
//   NimMain();
//   if (enableTrueColor) {
//       enableTrueColors();
//       if (!isTrueColorSupported()){
//           throw std::runtime_error("you wanna enable console true color, \n"
//           "but your console doesn't support it, considering disable it");
//       }
//       atexit(disableTrueColors);
//   }
// }

#define _NFII(sym) \
  void sym(NI x, NI y){return sym(stdout, x, y);}


_NFII( setCursorPos )


#undef _NFII


#define _NFI(sym) \
  void sym(NI n){return sym(stdout, n);}

// _NFI( setCursorXPos )

//_NFI( setCursorYPos ) // only support in windows


// _NFI( cursorUp )
// _NFI( cursorDown )

// _NFI( cursorForward )
// _NFI( cursorBackward )


#undef _NFI



#define _FBcB(sym, en) \
  void sym(en _color, bool bright/*=false*/){sym(stdout, _color, bright);}

_FBcB( setBackgroundColor, BackgroundColor )
_FBcB( setForegroundColor, ForegroundColor )
#undef _FBcN


ncolor::Base::Base(int rgb){
      if ( rgb<0 || rgb>0xffffff)
        throw std::invalid_argument(
          "expect color in range 0..0xffffff");
      data = rgb;
}

// ncolor::Base::Base(int r, int g, int b){
//       data = ntermC_rgb(r, g, b);}

//     // @throw `std::invalid_argument`
// ncolor::Base::Base(const char* name){
//       data = ntermC_parseColor(name);}

NI ncolor::Base::toNInt() const{return data;}

/*
#define DerivedInits(cls) \
    ncolor::cls::cls(int rgb): Base(rgb){}\
    ncolor::cls::cls(int r, int g, int b): Base(r, g, b){}\
    ncolor::cls::cls(const char* name): Base(name){}


DerivedInits(bg)
DerivedInits(fg)
*/

#undef DerivedInits


#define _genColor(fun) \
void fun(FILE*f, ncolor::Base c){\
    fun##RGB(f, c.toNInt() );\
}\
void fun(ncolor::Base c){fun(stdout, c);}\
void fun(int r, int g, int b){\
    fun(ncolor::Base(r, g, b));\
}
//end_define

// _genColor( setBackgroundColor )
// _genColor( setForegroundColor )


void setStyle(FILE* f, Style s){setStyle(f, StyleSet{s});}


#define _genAttr(T, fun) \
void setConsoleAttr(FILE*f, T c){fun(f, c);}

_genAttr( BackgroundColor, setBackgroundColor )
// _genAttr( ncolor::bg, setBackgroundColor )
_genAttr( ForegroundColor, setForegroundColor )
// _genAttr( ncolor::fg, setForegroundColor )
_genAttr( StyleSet, setStyle )
_genAttr( Style, setStyle )
#undef _genAttr



#if __cplusplus < 202000L
#else
void styledWriteLine(const char* s){
    fputs(s, f);
    resetAttributes(f);
    putc('\n', f);
}
#endif
