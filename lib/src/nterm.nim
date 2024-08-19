
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

proc writeStyled*(s: cstring, ils: InitList[Style]){.exportc, dynlib.} =
  var styles: set[Style]
  for i in cint(0)..<ils.size:
    styles.incl ils[i]
  writeStyled($s, styles)


