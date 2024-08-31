#include <iostream>
#include <string>
#include <ios>
#include <cstdlib>
#include "../include/combat.h"
#include "../include/equip.h"

class Room{
public:
    char posR[10][10];
    Room(Hero& h,int p = 7);
    void showRoom();
    void actionRoom();
private:
    int position;
    int dx, dy;
    int positionR;
    Hero h;
};
class Map{
public:
   char pos[10][10];
   Map(int p = 7) ;
   void showMap() ;
   void action();
   void showMenu();
private:
    int position;
    int dx, dy;
    Hero h;
};