#include <iostream>
#include <string>
#include <ios>
#include <cstdlib>

class Room{
public:
    char posR[10][10];
    Room(int p = 7);
    int getPositionR() ;
    void showRoom();
    void actionRoom();
private:
    int position;
    int dx, dy;
    int positionR;
};
class Map{
public:
   char pos[10][10];
   Map(int p = 7) ;
   void showMap() ;
   void showPosition() ;
   void action();
   void showMenu();
//    bool isCombat();
//    bool isChat();
   int getPosition();
   //string getName();
private:
    int position;
    int dx, dy;
};