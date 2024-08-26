
#include "../../include/map.h"

#include <windows.h>


int main(){
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Map myMap = Map(7);      
    while(1){
       myMap.showMap();
        myMap.showMenu();
        myMap.action();
    }
}
// using namespace std;
// int main(){
//     Map myMap = Map(7);      
//     while(1){
//         myMap.showMap();
//         myMap.showMenu();
//         myMap.action();
//     }        
// }
    
// // #include "../../include/map.h"
// #include <iostream>
// #include <string>
// #include <ios>
// #include <cstdlib>

// using namespace std;
// char mapName[11][50] = {"卧龙山", "祸窟", "地宫", "北阳山", "藏经阁", "郊外", "锻造屋", "中央主城", "药铺", "道远村", "郊外"};


// class Enemy{
// public:
//     string getname(){
//         return name;
//     }
//     int gettype(){
//         return type;
//     }
//     int gethealth(){
//         return health;
//     }
//     int getattack(){
//         return attackNum;
//     }
//     int getdefend(){
//         return defendNum;
//     }
//     string getawards(){
//         return awards;
//     }
// private:
//     string name;
//     int type;
//     int health;
//     int attackNum;
//     int defendNum;
//     string awards;
// };

// class Hero{
// public:
//     string getname(){
//         return name;
//     }
//     char getgender(){
//         return gender;
//     }
//     int gethealth(){
//         return health;
//     }
//     int getmagic(){
//         return magic;
//     }
//     int getattack(){
//         return attack;
//     }
//     int getdefend(){
//         return defend;
//     }
//     int getexp(){
//         return exp;
//     }
//     int getlevel(){
//         return level;
//     }
//     int getmoney(){
//         return money;
//     }

// private:
//     string name;
//     char gender;
//     int health;
//     int magic;
//     int attack;
//     int defend;
//     int exp;
//     int level;
//     int money;
// };

// class Map{
// public:
//     Map() {};

// };

// class Room{
// public:
//     char posR[10][10];
//     Room(int p = 7){
//         position = p;
//         dx = 1;
//         dy = 1;
//         positionR = 4;

//         for (int i = 0; i < 3;i++){
//             for (int j = 0; j < 3; j++)
//             {
//                 posR[i][j] = ' ';
//             }
//         }
//         posR[1][1] = '*';
//         posR[2][2] = '&';
//     }
//     int getPositionR() { return positionR; }


//     void showRoom() 
//     {
//         if (position == 4 || position == 6 || position == 7 || position == 8){
//             posR[0][0] = '#';
//         }
//         if (position == 1 || position == 3 || position == 2 || position == 9){
//             int enemyNum = 0;
//             while(!enemyNum){
//                 enemyNum = rand() % 4;
//             }
//             for (int i = 0; i < enemyNum;i++){
//                 int randomNum = rand() % 7;
//                 if (randomNum == 0 || posR[0][0] != '#'){
//                     posR[0][0] = '#';
//                 }
//                 if (randomNum == 0 && posR[0][0] =='#'){
//                     randomNum++;
//                 }

//                 if (randomNum == 1 || posR[0][1] != '#'){
//                     posR[0][0] = '#';
//                 }
//                 if (randomNum == 1 && posR[0][1] =='#'){
//                     randomNum++;
//                 }
//                 if (randomNum == 2 || posR[0][2] != '#'){
//                     posR[0][0] = '#';
//                 }
//                 if (randomNum == 2 && posR[0][2] =='#'){
//                     randomNum++;
//                 }
//                 if (randomNum == 3 || posR[1][0] != '#'){
//                     posR[0][0] = '#';
//                 }
//                 if (randomNum == 3 && posR[1][0] =='#'){
//                     randomNum++;
//                 }
//                 if (randomNum == 4 || posR[1][2] != '#'){
//                     posR[0][0] = '#';
//                 }
//                 if (randomNum == 4 && posR[1][2] =='#'){
//                     randomNum++;
//                 }
//                 if (randomNum == 5 || posR[2][0] != '#'){
//                     posR[0][0] = '#';
//                 }
//                 if (randomNum == 5 && posR[2][0] =='#'){
//                     randomNum++;
//                 }
//                 if (randomNum == 6 || posR[2][1] != '#'){
//                     posR[0][0] = '#';
//                 }
//                 if (randomNum == 6 && posR[2][1] =='#'){
//                     randomNum++;
//                 }
                

//             }
                

//         }
//             system("cls");
//         cout << mapName[position] << endl;
//         cout << "      _____________________" << endl;
//         cout << "      |                    |" << endl;
//         cout << "      |  "<<posR[0][0]<<"     "<<posR[0][1]<<"     "<<posR[0][2]<<"     |" << endl;
//         cout << "      |                    |" << endl;
//         cout << "      |  "<<posR[1][0]<<"     "<<posR[1][1]<<"     "<<posR[1][2]<<"     |" << endl;
//         cout << "      |                    |" << endl;
//         cout << "      |                    |" << endl;
//         cout << "      |  "<<posR[2][0]<<"     "<<posR[2][1]<<"     "<<posR[2][2]<<"     |" << endl;
//         cout << "      |____________________|" << endl;
//         cout << "      |" << "______";
//         cout << "______|" << endl;
        
        
//         switch (position)
//         {

//         case 4:
//             cout << " '#'处可学习技能" << endl;
//         case 6:
//             cout << "'#'处可打造你的装备" << endl;
//         case 7:
//             cout << "'#'处可购买物品" << endl;
//         case 8:
//             cout << "'#'处可治疗和制造药品" << endl;
//         case 1:
//             cout << "'#'处可与怪物战斗" << endl;
//         case 2:
//             cout << "'#'处可与怪物战斗" << endl;
//         case 3:
//             cout << "'#'处可与怪物战斗" << endl;
//         case 9:
//             cout << "'#'处可与怪物战斗" << endl;

//         default:
//             break;
//         }


//     }
    
//     void actionRoom(){
//         cout << "输入wasd来移动" << endl;
//         char order;
//         cin >> order;
//         switch(order){
//             case 'w':{
//                 if (positionR == 0 || positionR == 1 || positionR == 2){
//                     cout << "无法移动";
//                 }
//                 else {
//                     positionR -= 3;
//                     dx--;
//                     }
//                 break;
//             }
//             case 'a':{
//                 if (positionR == 0 || positionR == 3 || positionR == 6){
//                     cout << "无法移动";
//                 }
//                 else{
//                     positionR--;
//                     dy--;
//                 }
//                 break;
//             }
//             case 'd':{
//                 if (positionR == 2 || positionR == 5 || positionR == 8){
//                     cout << "无法移动" << endl;
//                 }
//                 else{
//                     positionR++;
//                     dy++;
//                 }
//                 break;
//             }
//             case 's':{
//                 if (positionR == 6 || positionR == 7 || positionR == 8){
//                     cout << "无法移动" << endl;
//                 }
//                 else{
//                     dx++;
//                     positionR += 3;
//                 }
//                 break;
//             }
//             default:
//                 break;
//         }
//         posR[dx][dy] = '*';
//         if ((position == 4 || position == 6 || position == 7 || position == 8) && positionR == 0)
//         {
//             cout << "这里有对话" << endl;
//         }
//         if ((posR[dx][dy] == '#') && (position == 1 || position == 3 || position == 2 || position == 9))
//         {
//             cout << "这里发生战斗" << endl;
//         }
//         if (posR[dx][dy] == '&'){
//             Map tempMap = Map(7);
//             tempMap.showMap();
//                 }
            
//     }
    
// private:
//     int position;
//     int dx, dy;
//     string type;
//     int positionR;
// };

// class Map{
// public:
    
//     char pos[10][10];
//     Map(int p = 7)
//     {

        
//         position = p;
        
//         if (p == 0){
//             dx = 2;
//             dy = 0;
//         }
//         if (p == 1){
//             dx = 2;
//             dy = 1;
//         }
//         if (p == 2){
//             dx = 0;
//             dy = 2;
//         }
//         if (p == 3){
//             dx = 1;
//             dy = 2;
//         }
//         if (p == 4){
//             dx = 2;
//             dy = 2;
//         }
//         if (p == 5){
//             dx = 3;
//             dy = 2;
//         }
//         if (p == 6){
//             dx = 1;
//             dy = 3;
//         }
//         if (p == 7){
//             dx = 2;
//             dy = 3;
//         }
//         if ( p == 8){
//             dx = 2;
//             dy = 4;
//         }
//         if (p == 9){
//             dx = 2;
//             dy = 5;
//         }

//         for (int i = 0; i < 6; i++)
//         {
//             for (int j = 0; j < 6; j++)
//             {
//                 pos[i][j] = ' ';
//             }
//         }
//         pos[dx][dy] = '*';
//     }
//     void showMap(){
//     cout << "世界地图:" << endl;
// 	cout<<"                        __________"<<endl;
// 	cout<<"                       |          |"<<endl;
// 	cout<<"                       |   卧龙山 |"<<endl;
//     cout << "                       |   " << pos[2][0] << "      |" << endl;
//     cout<<"                       |__________|"<<endl;
// 	cout<<"                       |          |"<<endl;
// 	cout<<"                       |   祸窟   |"<<endl;
//     cout << "                       |     " << pos[2][1] << "    |" << endl;
//     cout<<"_______________________|__________|__________"<<endl;
// 	cout<<"|          |          |           |          |"<<endl;
// 	cout<<"|   地宫   |   北阳山 |   藏经阁  |   郊外   |"<<endl;
//     cout << "|    " << pos[0][2] << "     |     " << pos[1][2] << "    |     "<< pos[2][2] << "     |    " << pos[3][2] << "     |" << endl;
//     cout<<"|__________|__________|___________|__________|"<<endl;
//     cout << "           |          |          |          |" << endl;
//     cout<<"           |   锻造屋 | 中央主城 |   药铺   |"<<endl;
//     cout << "           |     " << pos[1][3] << "    |      " << pos[2][3] << "   |    " << pos[3][3] << "     |" << endl;
//     cout<<"           |__________|__________|__________|"<<endl;
// 	cout<<"                      |          |"<<endl;
// 	cout<<"                      |   道远村 |"<<endl;
//     cout<<"                      |    "<< pos[2][4] <<"     |"<<endl;
// 	cout<<"                      |__________|"<<endl;
// 	cout<<"                      |          |"<<endl;
// 	cout<<"                      |    郊外  |"<<endl;
//     cout<<"                      |    "<< pos[2][5] <<"     |"<<endl;
// 	cout<<"                      |__________|"<<endl;
//     }
    

//     void action(){
//         char command;
        
//         cin >> command;
//         pos[dx][dy] = ' ';
//         switch (command){
//         case 'w':{
//             if (position == 0 || position == 2 || position == 3 || position == 5){
//                 cout << "移动失败" << endl;
//                 break;
//             }
//             if (position == 1 || position == 10)
//             {
//                 dy--;
//                 position -= 1;
//                 break;
//             }
//             if (position == 4 || position == 6 || position == 7 || position == 8){
//                 dy--;
//                 position -= 3;
//                 break;
//             }
//             if (position == 9){
//                 dy--;
//                 position -= 2;
//                 break;
//             }
//             break;
//         }
//         case 'a':{
//             if (position == 2 || position == 0 || position == 1 || position == 6 || position == 9 || position == 10)
//                 {
//                     cout << "移动失败" << endl;
//                     break;
//                 }
//                 if (position == 3 || position == 4 || position == 5 || position == 7 || position == 8){
//                     dx--;
//                     position--;
//                 }
//                 break;
//         }
//         case 'd':{
//             if (position == 1 || position == 5 || position == 8 || position == 9 || position == 10 || position == 0)
//             {
//                 cout << "无法移动" << endl;
//             }
//             if (position == 2 || position == 3 || position == 4 || position == 6 || position == 7){
//                 dx++;
//                 position++;
//             }
//             break;
//         }
//         case 's':{
//             if (position == 2 || position == 6 || position == 10 || position == 8){
//                 cout << "无法移动" << endl;
//                 break;
//             }
//             if (position == 3 || position == 4 || position == 5 || position == 1){
//                 dy++;
//                 position += 3;
//                 break;
//             }
//             if (position == 7){
//                 dy++;
//                 position += 2;
//                 break;
//             }
//             if (position == 9 || position == 0)
//             {
//                 dy++;
//                 position++;
//                 break;
//             }
//         }
//         case 'm':{
            
//             Room myRoom = Room(position);
//             myRoom.showRoom();
//         }

//         default:
//             break;
//         }
//         pos[dx][dy] = '*';
        
//     }
        
//     // Map(){
// 	// position = 0;
// 	// dx = 5;
// 	// dy = 2;

// 	// for (int i = 0; i < 6; i++)
// 	// {
// 	// 	for (int j = 0; j < 6; j++)
// 	// 	{
// 	// 		pos[i][j] = ' ';
// 	// 	}
// 	// }
// 	// pos[dx][dy] = '*';
// // }
//     bool isCombat(){
//         if (position == 0 || position == 1 || position == 2 || position == 3 || position == 9){
//             return true;
//         }
//         else
//             return false;
//     }
//     bool isChat(){
//         if (position == 4 || position == 6 || position == 8){
//             return true;
//         }
//         else
//             return false;
//     }

//     int getPostion(){
//         return position;
//     }
//     string getName(){
//         return mapName[position];
//     }

//     void showMenu(){
//         cout << "您目前的位置是：" << mapName[position] << endl;
//         cout << "1.输入m进入区域。"<<endl;
//         cout << "2.输入wasd以移动" << endl;
        
//     }
// private:
//     int position;
//     int dx, dy;
// };



// //鼠标点击


// /*class Scene{
// private:
//     string name;
//     char type;
// public:
//     void move(){

//     }
// };
// class Scene1:public Scene{
// public:
//     Scene1(string name):Scene(name){

//     }
//     void showMenu(){
//         cout << "菜单"<<endl;
//         cout << "1.继续前进" << endl;
//         cout << "2.与npc交谈" << endl;
//     }
// };

// /*class Scene2:Scene{
//     void showmenu(){
//         cout << "菜单" << endl;
//         cout << "1.继续前进" << endl;
//         cout << "2.战斗" << endl;
//     }
// };*/


