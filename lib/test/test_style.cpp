
#include "../terminal.h"

#include <iostream>
int main(){
  ntermInit();
  writeStyled(
    "this shall be italic",
    {styleItalic}
  );
  writeStyled(
    " bright\n"
  );
}
