
#include "../terminal.h"

#include <iostream>
int main(){
  writeStyled(
    "this shall be italic",
    {styleItalic}
  );
  writeStyled(
    " bright\n"
  );
}
