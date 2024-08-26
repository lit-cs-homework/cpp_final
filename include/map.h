#include <iostream>
#include <string>

class Map{
public:
   char mapName[11][50] = {"卧龙山", "祸窟", "地宫", "北阳山", "藏经阁", "郊外", "锻造屋", "中央主城", "药铺", "道远村", "郊外"};
   char pos[10][10];
   Map(int p = 7) {}
   void showMap() {}
   void showPosition() {}
   void move(){}
   bool isCombat(){}
   bool isChat(){}
   int getPosition(){}
   string getName(){}
private:
    int postion;
    int dx, dy;
}