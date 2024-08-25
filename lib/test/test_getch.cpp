

#include "../nterm.h"

#include <iostream>
int main(){
  ntermInit();
  writeStyled(
    "asdasd",
    {styleItalic}
  );
  writeStyled(
    "please press any key to continue"
  );
  writeStyled(
    "... ", {}
  );
  getch();
}
