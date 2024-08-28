
#include "../../include/map.h"

#include <windows.h>

int main(){
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Map myMap = Map(7);      
    while(1){
        myMap.showMap();
        myMap.showMenu();
        myMap.action();
    }
}
