#include "../../include/equip.h"
#include "../../include/scenario.h"
#include "../../lib/nterm.h"
#include "../../include/equip.h"
int main()
{
    ntermInit();
    Hero h;
    Scenario s(h);
    s.adjustScenario(7);
    s.Dungeon();
    return 0;
}