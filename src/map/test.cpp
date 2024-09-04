
#include "../../include/map.h"
#include "../../include/combat.h"
#include "../../include/equip.h"
#include "../../include/backup.h"


#ifdef _WIN32
#include <windows.h>
#endif

int main(){
    // {
    //     Map myMap = Map(7);
    //     auto s = hps::to_string(myMap);
    //     Map nMap = hps::from_string<Map>(s);

    // }
    ntermInit();
    /*
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    */
   
    Map myMap = Map(7);
    do{
        myMap.showMap();
        myMap.showMenu();

    } while (myMap.action());
}
