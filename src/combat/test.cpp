
#include "../../include/combat.h"

#include "../../include/equip.h"
#include "../../lib/nterm.h"

#include <iostream>
int main()
{
    ntermInit();
    /*
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif*/
    srand((unsigned int)time(NULL));
    Skill s2("凌天一斩", "奋力向对方发动一次斩击。 ", 40, 20);
    Hero h;
    h.setName();
    h.setSkill(s2);
    std::shared_ptr<RedMedicine> redMedicine = std::make_shared<RedMedicine>() ;
    h.getBag().get(redMedicine,10);
    //fightTunnel(&h);
    std::cout<<"11";
    cursorDown(1);
    std::cout<<"22";
    return 0;
}
