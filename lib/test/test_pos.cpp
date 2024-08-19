
#include "../terminal.h"

#include <iostream>

int main(){
  ntermInit();
  NI x, y;
  getCursorPos(x, y);
  std::cout << x << ' ' << y << std::endl;
  //std::cout << terminalWidth() << std::endl;
 
  getCursorPos(x, y);
  std::cout << x << ' ' << y << std::endl;
 
  setCursorPos(stdout, 15, 6);
  std::cout << 1 << std::endl;
}
