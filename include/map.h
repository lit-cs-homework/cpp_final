#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <cstdlib>
#include "../lib/nterm.h"
#include "../lib/hps/hps.h"
#include "../include/combat.h"
#include "../include/equip.h"
#include "../include/backup.h"
#include "../include/scenario.h"

class Room{
public:
    char posR[10][10];
    Room(Hero& h,Store& store,int p = 7);
    void showRoom();
    void actionRoom();
    
    template <class B>
    void serialize(B& buf) const {
        buf << position << dx << dy;

    }

    template <class B>
    void parse(B& buf) {
        buf >> position >> dx >> dy;
    }
private:
    int position;
    int dx, dy;
    int positionR;
    Store& store;
    Hero& h;
};
  
class Map{
public:
   char pos[10][10];
   Map(int p = 7) ;
   void showMap() ;
   bool action();
   void showMenu();
    template <class B>
    void serialize(B& buf) const {
        buf << position << dx << dy << h << store << sc;
    }

    template <class B>
    void parse(B& buf) {
        buf >> position >> dx >> dy >> h >> store >> sc;
    }
private:
    int position;
    int dx, dy;
    Store store;
    Hero h;
    std::fstream backupFile;
    Scenario sc;
};