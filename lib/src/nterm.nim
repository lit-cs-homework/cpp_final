
import ./terminal
export terminal

const Version* = "0.0.2"
let version = cstring Version
proc nterm_getVersion*(): cstring{.exportc, dynlib.} =
  version

import std/colors
type
  CStdException* {.importcpp: "std::exception", header: "<exception>", inheritable.} = object
  InvArgErr*{.importcpp:"std::invalid_argument", header: "<stdexcept>",
  .} = object of CStdException
proc what*(s: CStdException): cstring {.importcpp: "((char *)#.what())".}
proc initInvArgErr*(a: cstring): InvArgErr {.importcpp: "std::invalid_argument(@)", constructor.}
proc initInvArgErr*(a: string): InvArgErr{.noInit  # noInit is required to pass compilation
  .} = initInvArgErr cstring a


const rRGB = cint(0)..cint(255)
type
  RGB = range[0..255]
func chk255(x: cint): RGB =
  if x not_in rRGB:
    raise initInvArgErr cstring("not in" & $rRGB)
  cast[RGB](x)

{.pragma: exportNC, exportc: "ntermC_$1", dynlib, raises: [InvArgErr].}
proc rgb*(r, g, b: cint): Color{.exportNC.} =
  rgb(chk255 r,
      chk255 g,
      chk255 b)

proc parseColor*(name: cstring): Color{.exportNC.} =
  try:
    result = parseColor $name
  except ValueError as e:
    raise initInvArgErr e.msg

template wrapXY(sym, x, y) =
  let res = sym()
  x = res.x
  y = res.y

proc getCursorPos*(x, y: var int){.exportc, dynlib.} =
   wrapXY(getCursorPos, x, y)
proc terminalSize*(w, h: var int){.exportc, dynlib.} =
   wrapXY(terminalSize, w, h)
    

#type Styles{.importcpp:"".} = array
#proc writeStyled*(txt: cstring, style: set[Style] = {styleBright}){.exportc: "_$1CStrSet", dynlib.}

type
  InitList[T]{.importcpp: "std::vector", header: "<vector>"} = object
proc `[]`[T](self: InitList[T], i: cint): T{.importcpp: "#[#]".}
proc size[T](self: InitList[T]): cint{.importcpp.}

type StyleSet = InitList[Style]

template toSet[T](ils: InitList[T]): set[T] =
  var s: set[T]
  for i in cint(0)..<ils.size:
    s.incl ils[i]
  s

proc setStyle*(f: File, ils: StyleSet){.exportc, dynlib.} =
  f.setStyle ils.toSet

proc writeStyled*(s: cstring, ils: StyleSet){.exportc, dynlib.} =
  writeStyled($s, ils.toSet)

when defined(windows) and appType != "gui" and
    not defined(nimDontSetUtf8CodePage) and not defined(nimscript):
  import std/exitprocs

  proc setConsoleOutputCP(codepage: cuint): int32 {.stdcall, dynlib: "kernel32",
    importc: "SetConsoleOutputCP".}
  proc setConsoleCP(wCodePageID: cuint): int32 {.stdcall, dynlib: "kernel32",
    importc: "SetConsoleCP".}
  proc getConsoleOutputCP(): cuint {.stdcall, dynlib: "kernel32",
    importc: "GetConsoleOutputCP".}
  proc getConsoleCP(): cuint {.stdcall, dynlib: "kernel32",
    importc: "GetConsoleCP".}

  const Utf8codepage = 65001'u32

  let
    consoleOutputCP = getConsoleOutputCP()
    consoleCP = getConsoleCP()

  proc restoreConsoleOutputCP() = discard setConsoleOutputCP(consoleOutputCP)
  proc restoreConsoleCP() = discard setConsoleCP(consoleCP)

  if consoleOutputCP != Utf8codepage:
    discard setConsoleOutputCP(Utf8codepage)
    addExitProc(restoreConsoleOutputCP)

  if consoleCP != Utf8codepage:
    discard setConsoleCP(Utf8codepage)
    addExitProc(restoreConsoleCP)

