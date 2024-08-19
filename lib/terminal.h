

#ifndef _NIM_TERMINAL_H
#define _NIM_TERMINAL_H

#include <cstdint>

typedef void* POINTER;
constexpr int NIM_INTBITS = (8 * sizeof(POINTER));
//#define NIM_INTBITS (8 * sizeof(POINTER))

#define _NIN(n) typedef int##n##_t NI##n; typedef uint##n##_t NU##n;
_NIN(64)
_NIN(32)
_NIN(16)
_NIN(8)

static_assert(NIM_INTBITS==64);
typedef NI64 NI;
typedef NU64 NU;

/*
#  if NIM_INTBITS == 64
typedef NI64 NI;
typedef NU64 NU;
#  elif NIM_INTBITS == 32
typedef NI32 NI;
typedef NU32 NU;
#  elif NIM_INTBITS == 16
typedef NI16 NI;
typedef NU16 NU;
#  elif NIM_INTBITS == 8
typedef NI8 NI;
typedef NU8 NU;
#  else
#    error "invalid bit width for int"
#  endif
*/
#include <cstdio>

#define _PRE extern "C" 

_PRE char getch(void);

#define _RI(sym) _PRE NI sym(void);

_RI( terminalWidth )
_RI( terminalHeight )


#define _VIVI(sym) _PRE void sym(NI&, NI&);

_VIVI( getCursorPos )


#define _FII(sym) _PRE void sym(FILE*, NI, NI);

_FII( setCursorPos )

#define _FI(sym) _PRE void sym(FILE*, NI);

_FI( setCursorXPos )
_FI( setCursorYPos )


_FI( cursorUp )
_FI( cursorDown )

_FI( cursorForward )
_FI( cursorBackward )


#define _F(sym) _PRE void sym(FILE* _file=stdout);

_F( eraseLine )
_F( eraseScreen )
_F( resetAttributes )

_F( hideCursor )
_F( showCursor )


#define _VV(sym) _PRE void sym(void);

_VV( enableTrueColors )
_VV( disableTrueColors )

#define _BV(sym) _PRE bool sym(void);
_BV( isTrueColorSupported )

_FI( setBackgroundColorRGB )
_FI( setForegroundColorRGB )

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

#define _FBcB(sym, en) _PRE void sym(FILE* _file, en _color, bool bright=false);
_FBcB( setBackgroundColor, BackgroundColor )
_FBcB( setForegroundColor, ForegroundColor )


enum
 Style{
  styleBright = 1,          // bright text
  styleDim,                 // dim text
  styleItalic,              // italic (or reverse on terminals not supporting)
  styleUnderscore,          // underscored text
  styleBlink,               // blinking/bold text
  styleBlinkRapid,          // rapid blinking/bold text (not widely supported)
  styleReverse,             // reverse
  styleHidden,              // hidden text
  styleStrikethrough        // strikethrough
 };


#include <vector>

_PRE void writeStyled(
  const char* s,
  std::vector<Style> styles = {styleBright});


#endif  // _NIM_TREMINAL_H
