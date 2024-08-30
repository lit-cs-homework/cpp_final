#include "../../lib/nterm.h"
#include "../../include/map.h"
#include "../../include/combat.h"
#include "../../include/equip.h"


#ifdef _WIN32
#include <windows.h>
#endif

int main(){
    ntermInit();
    /*
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    */
    Map myMap = Map(7);      
    while(1){
        myMap.showMap();
        myMap.showMenu();
        myMap.action();
    }
}
