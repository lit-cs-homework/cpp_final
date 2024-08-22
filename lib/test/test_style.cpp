
#include "../nterm.h"

#include <iostream>
int main(){
  ntermInit();
  styledWrite(
    ncolor::bg("blue"), ncolor::fg(255, 0, 0), styleItalic,
    "this shall be italic with blue bg and red fg"
  );
  styledWriteLine(styleBright,
    " bright"
  );
  std::cout << "asdsa\n";
}
