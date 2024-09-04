#include "../../include/equip.h"
#include "../../include/scenario.h"
#include "../../lib/nterm.h"
#include "../../include/equip.h"
int main()
{
    ntermInit();
    Hero h;
    Scenario s(h);
    s.adjustScenario(1);
    s.Tunnel();
    return 0;
}