
import ./terminal

export terminal

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

