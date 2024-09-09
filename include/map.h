#pragma once

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
    Room(Hero& h, Store& store , Scenario& scm, int p = 7);
    void showRoom();
    void mainloop();
    void communciateNpc(int position);
    void roomBattle(int pos);
    template <class B>
    void serialize(B& buf) const {
        buf << position << dx << dy;

    }

    template <class B>
    void parse(B& buf) {
        buf >> position >> dx >> dy;
    }
    void createEnemy(int position, int dx, int dy);
    void updateAffair(int position);
private:
    int position;
    int dx, dy;
    int positionR;
    Store& store;
    Hero& h;
    Scenario& sc;
};
  
class Map{
public:
   char pos[10][10];
   Map(int p = 7) ;
   void enterFirstScenario();
   /// @brief will be auto called in `load`
   void prepareShowMap();
   void showMap() ;
   bool action();
   void showMenu();
   bool hasBackup();
   /// @returns if @param backup data is loaded
   bool load(Backup& backup);
   /// @returns if previous data is loaded
   bool load();
   bool delBackup();
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
    Backup backup;
    Scenario sc;
};