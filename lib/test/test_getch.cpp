

#include "../terminal.h"

#include <iostream>
int main(){
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
