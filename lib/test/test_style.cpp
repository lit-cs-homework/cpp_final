
#include "../nterm.h"

#include <iostream>
int main(){
  ntermInit();
  std::cout << "asdsa\n";
  styledWrite(bgGreen, fgRed,
    "this shall be italic with green bg and red fg"
  );
  styledWriteLine(styleBright,
    " bright"
  );
  std::cout << "asdsa\n";
}
