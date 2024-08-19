
#include "../nterm.h"

#include <iostream>

int main(){
  ntermInit();
  NI x, y;
  getCursorPos(x, y);
  std::cout << x << ' ' << y << std::endl;
  //std::cout << terminalWidth() << std::endl;

  getCursorPos(x, y);
  std::cout << x << ' ' << y << std::endl;
 
  setCursorPos(15, 6);
  std::cout << "asdasdsad" << std::endl;
  setCursorPos(x, y);
  cursorForward(3);

}
