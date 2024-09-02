#include "../../include/map.h"
#include "../../include/combat.h"
#include "../../include/equip.h"
#include <cstdlib>
#include <string>

#ifdef _WIN32
# include<windows.h>
#else
//#include <unistd.h>
#endif

static
void ms_sleep(int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	struct timespec tp = {
		ms / 1000,    // second
		ms % 1000000  // ns
	};
	nanosleep(&tp, NULL);
#endif
}

using std::cin;
using std::cout;
using std::endl;
//const char* mapName[11] = {"卧龙山", "祸窟", "地宫", "北阳山", "藏经阁", "郊外", "锻造屋", "中央主城", "药铺", "道远村", "郊外"};
std::string mapName[11] = {"卧龙山", "祸窟", "地宫", "北阳山", "藏经阁", "郊外", "锻造屋", "中央主城", "药铺", "道远村", "郊外"};
std::string mapName2[11] = {"  卧龙山  ", "   祸窟   ", "   地宫   ", "  北阳山  ", "  藏经阁  ", "   郊外   ", "  锻造屋  ", " 中央主城 ", "   药铺   ", "  道远村  ", "   郊外   "};



// void arrangeMapName(std::string mapName[]){
//     for (int i = 0; i < 11; i++) {
//         std::string tempname = mapName[i];
//         int length = tempname.length();
//             tempname += std::string(4 - length, ' ');
//             tempname.insert(length / 2, ' ');
//         mapName[i] = tempname.c_str();
//     }
// }
const char* const mapsName[][6][4] =
{
{
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""} 
},

{
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""} 
},

{
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""}, 
  {"",      "",      "",      ""} 
}
}
;


static void CannotMove()
{
    cout << "无法移动" << endl;
}
bool isRandom(int randomNum1,int randomNum2,int randomNum3,int n){
    if (randomNum1 == n || randomNum2 == n || randomNum3 == n){
        return true;
    }
    else
        return false;
}
Room::Room(Hero &hm,Store& storem, int p):h(hm),store(storem)
{

    position = p;
    dx = 1;
    dy = 1;
    positionR = 4;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            posR[i][j] = ' ';
        }
    }
    posR[1][1] = '*';
    posR[2][2] = '&';
    if (position == 4 || position == 6 || position == 7 || position == 8)
    {
        posR[0][0] = '#';
    }

    if (position == 1 || position == 3 || position == 2 || position == 9)
    {
        int enemyNum = 0;
        int randomNum1 = 97;
        int randomNum2 = 98;
        int randomNum3 = 99;
        while (!enemyNum)
        {
            srand(time(NULL));
            enemyNum = rand() % 4;
        }
        switch (enemyNum){
            case 1:{
                randomNum1 = rand() % 7;
                break;
            }
            case 2:{
                randomNum1 = rand() % 7;
                randomNum2 = rand() % 7;
                break;
            }
            case 3:{
                randomNum1 = rand() % 7;
                randomNum2 = rand() % 7;
                randomNum3 = rand() % 7;
            }
               
            
        }   
            while(randomNum1==randomNum2){
                randomNum1 = rand() % 7;
            }
            while (randomNum2 == randomNum3){
                randomNum2 == rand() % 7;
            }
            #define check3is(N) isRandom(randomNum1,randomNum2,randomNum3,N)
            if (check3is(0)){
                posR[0][0] = '!';
            }
            else
            if (check3is(1)){
                posR[0][1] = '!';
            }
            else
            if (check3is(2)){
                posR[0][2] = '!';
            }
            else
            if (check3is(3)){
                posR[1][0] = '!';
            }
            else
            if (check3is(4)){
                posR[1][2] = '!';
            }
            else
            if (check3is(5)){
                posR[0][0] = '!';
            }
            else
            if (check3is(6)){
                posR[2][1] = '!';
            }
            #undef check3is
        
    }
}
static void showTips(std::string tips){
    cout << "'#':移动至此可" << tips << '\n';
}

void Room::showRoom()
{
    eraseScreen();
    setCursorPos(0, 0);
    cout << "             " << mapName[position] << '\n';
    cout << "       ____________________" << '\n';
    cout << "      |                    |" << '\n';
    cout << "      |  " << posR[0][0] << "     " << posR[0][1] << "     " << posR[0][2] << "     |" << '\n';
    cout << "      |                    |" << '\n';
    cout << "      |  " << posR[1][0] << "     " << posR[1][1] << "     " << posR[1][2] << "     |" << '\n';
    cout << "      |                    |" << '\n';
    // cout << "      |                    |" << '\n';
    cout << "      |  " << posR[2][0] << "     " << posR[2][1] << "     " << posR[2][2] << "     |" << '\n';
    cout << "      |____________________|" << '\n';

    cout << "输入wasd在房间移动" << endl;
    cout << "'&':移动至此可退出地图" << '\n';

    switch (position)
    {
    case 4:
    {
        showTips("学习技能");
        break;
    }
    case 6:
    {
        showTips("打造装备");
        break;
    }
    case 7:
    {
        showTips("购买物品");
        break;
    }
    case 8:
    {
        showTips("购买药物");
        break;
    }
    case 1:
    case 2:
    case 3:
    case 9:
    {
        cout << "'!':移动至此可与怪物战斗" << '\n';
        break;
    }

    default:
        break;
    }
}

 static void communciateNpc(int position){
    switch(position){
        case 8:{
            cout << "这里是药铺" << endl;
            ms_sleep(700);
            break;
        }
        case 7:{
            cout << "这里是主城" << endl;
            ms_sleep(700);
            break;
        }
        case 6:{
            cout << "这里是锻造屋" << endl;
            ms_sleep(700);
            break;
        }
        case 4:{
            cout << "这里是藏经阁" << endl;
            ms_sleep(700);
            break;
        }
        default:{
            break;
        }
    }
}
void Room::actionRoom()
{
    char order = ' ';
    while (order != 'n')
    {
        order = getch();
        switch (order)
        {
        case 'w':
        {
            int temp = dx;
            temp--;
            if (positionR == 0 || positionR == 1 || positionR == 2)
            {
                CannotMove();
            }
            else if ((positionR == 3) && (position == 4 || position == 6 || position == 7 || position == 8))
            {
                communciateNpc(position);
            }
            else if ((position == 1 || position == 3 || position == 2 || position == 9) && posR[temp][dy] == '!')
            {
                eraseScreen();
                Fight(&h);
                positionR -= 3;
                dx--;
            }
            else
            {
                positionR -= 3;
                dx--;
            }
            break;
        }
        case 'a':
        {
            int temp = dy;
            temp--;
            if (positionR == 0 || positionR == 3 || positionR == 6)
            {
                CannotMove();
            }
            else if ((positionR == 1) && (position == 4 || position == 6 || position == 7 || position == 8))
            {
                communciateNpc(position);
            }
            else if ((position == 1 || position == 3 || position == 2 || position == 9) && posR[dx][temp] == '#')
            {
                eraseScreen();
                Fight(&h);
                positionR--;
                dy--;
            }
            else
            {
                positionR--;
                dy--;
            }
            break;
        }
        case 'd':
        {
            int temp = dy;
            temp++;
            if (positionR == 2 || positionR == 5 || positionR == 8)
            {
                CannotMove();
            }
            else if ((position == 1 || position == 3 || position == 2 || position == 9) && posR[dx][temp] == '!')
            {
                eraseScreen();
                Fight(&h);
                positionR++;
                dy++;
            }
            else
            {
                positionR++;
                dy++;
            }
            break;
        }
        case 's':
        {
            int temp = dx;
            temp++;
            if (positionR == 6 || positionR == 7 || positionR == 8)
            {
                CannotMove();
            }
            else if ((position == 1 || position == 3 || position == 2 || position == 9) && posR[temp][dy] == '#')
            {
                eraseScreen();
                Fight(&h);
                dx++;
                positionR += 3;
            }
            else
            {
                dx++;
                positionR += 3;
            }
            break;
        }
        default:
            break;
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if ((posR[i][j]) != '#' && (posR[i][j]) != '&'&&(posR[i][j]!='!'))
                {
                    posR[i][j] = ' ';
                }
            }
        }

        if (posR[dx][dy] == '&')
        {
            order = 'n';
            cout << "已回到主地图" << endl;
            return;
        }

        posR[dx][dy] = '*';

        Room::showRoom();
    }
}

Map::Map(int p /*=7*/)
{
    Hero h;
    Skill s2("凌天一斩", "奋力向对方发动一次斩击。 ", 40, 20);
    std::shared_ptr<BlueMedicine> bluemedicine = std::make_shared<BlueMedicine>() ;
    std::shared_ptr<RedMedicine> redMedicine = std::make_shared<RedMedicine>() ;
    std::shared_ptr<StoneSword> a = std::make_shared<StoneSword>() ;
    std::shared_ptr<IronSword> b = std::make_shared<IronSword>() ;
    std::shared_ptr<BronzeSword> c = std::make_shared<BronzeSword>();
    std::shared_ptr<Shoes> d = std::make_shared<Shoes>() ;
    std::shared_ptr<Armhour> e = std::make_shared<Armhour>() ;
    std::vector<std::shared_ptr<Equip>> equipstore = {a,b,c};
    std::vector<std::shared_ptr<Medicine>> medicinestore = {redMedicine,bluemedicine};
    Store store(equipstore,medicinestore);
    h.setSkill(s2);
    position = p;
#define dealStart(N, x, y)      case N: { dx = x;dy = y;break;}
    switch (p){
        dealStart(0,2,0)
        dealStart(1,2,1)
        dealStart(2,0,2)
        dealStart(3,1,2)
        dealStart(4,2,2)
        dealStart(5,3,2)
        dealStart(6,1,3)
        dealStart(7,2,3)
        dealStart(8,2,4)
        dealStart(9,2,5)
    } 
#undef dealStart
 

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            pos[i][j] = ' ';
        }
    }
    pos[dx][dy] = '*';
}

void Map::showMap()
{
    eraseScreen();
    setCursorPos(0, 0);
    cout << "世界地图:" << '\n';
    cout << "                       __________" << '\n';
    cout << "                      |          |" << '\n';
    cout << "                      |"<<mapName2[0]<<"|" << '\n';
    cout << "                      |    " << pos[2][0] << "     |" << '\n';
    cout << "                      |__________|" << '\n';
    cout << "                      |          |" << '\n';
    cout << "                      |"<<mapName2[1]<<"|" << '\n';
    cout << "                      |    " << pos[2][1] << "     |" << '\n';
    cout << "______________________|__________|___________" << '\n';
    cout << "|          |          |          |          |" << '\n';
    cout << "|"<<mapName2[2]<<"|"<<mapName2[3]<<"|"<<mapName2[4]<<"|"<<mapName2[5]<<"|" << '\n';
    cout << "|    " << pos[0][2] << "     |    " << pos[1][2] << "     |    " << pos[2][2] << "     |    " << pos[3][2] << "     |" << '\n';
    cout << "|__________|__________|__________|__________|" << '\n';
    cout << "           |          |          |          |" << '\n';
    cout << "           |"<<mapName2[6]<<"|"<<mapName2[7]<<"|"<<mapName2[8]<<"|" << '\n';
    cout << "           |    " << pos[1][3] << "     |    " << pos[2][3] << "     |    " << pos[3][3] << "     |" << '\n';
    cout << "           |__________|__________|__________|" << '\n';
    cout << "                      |          |" << '\n';
    cout << "                      |"<<mapName2[9]<<"|" << '\n';
    cout << "                      |    " << pos[2][4] << "     |" << '\n';
    cout << "                      |__________|" << '\n';
    cout << "                      |          |" << '\n';
    cout << "                      |"<<mapName2[10]<<"|" << '\n';
    cout << "                      |    " << pos[2][5] << "     |" << '\n';
    cout << "                      |__________|" << '\n';
    cout.flush();
}

// if not sleep, message will be erased.
static
void displayBelowMap(const char* const stringm){
    cout << stringm << endl;
    ms_sleep(700);
}

bool Map::action()
{
    pos[dx][dy] = ' ';
    char command = ' ';
    command = getch();
    // cin >> command;
    switch (command)
    {
    case 'w':
    {
        if (position == 0 || position == 2 || position == 3 || position == 5)
        {
            
            CannotMove();
        }
        else if (position == 1 || position == 10)
        {
            dy--;
            position -= 1;
        }
        else if (position == 4 || position == 6 || position == 7 || position == 8)
        {
            dy--;
            position -= 3;
        }
        else if (position == 9)
        {
            dy--;
            position -= 2;
        }
        eraseScreen();
        break;
    }
    case 'a':
    {
        if (position == 2 || position == 0 || position == 1 || position == 6 || position == 9 || position == 10)
        {
            CannotMove();
            break;
        }
        if (position == 3 || position == 4 || position == 5 || position == 7 || position == 8)
        {
            dx--;
            position--;
        }
        eraseScreen();
        break;
    }
    case 'd':
    {
        if (position == 1 || position == 5 || position == 8 || position == 9 || position == 10 || position == 0)
        {
            CannotMove();
        }
        if (position == 2 || position == 3 || position == 4 || position == 6 || position == 7)
        {
            dx++;
            position++;
        }
        eraseScreen();
        break;
    }
    case 's':
    {
        if (position == 2 || position == 6 || position == 10 || position == 8)
        {
            CannotMove();
            break;
        }
        if (position == 3 || position == 4 || position == 5 || position == 1)
        {
            dy++;
            position += 3;
            break;
        }
        if (position == 7)
        {
            dy++;
            position += 2;
            break;
        }
        if (position == 9 || position == 0)
        {
            dy++;
            position++;
            break;
        }
        
        break;
    }
    // case 'n':
    // {
    //     cout << "输入的是i" << endl;
    //     break;
    // }

    case 13:  // Enter
    {
        Room myRoom = Room(h,store, position);
        myRoom.showRoom();
        myRoom.actionRoom();
        break;
    }
    case 'v':
    {
        displayBelowMap("游戏进度已保存。");

        auto save = hps::to_string(*this);
        
        break;
    }
    case 3: // ctrl-c
    {
        return false;
    }
    case 0:
    {
        displayBelowMap("你按下了ctrl /↑/↓/←/→");

        break;
        
    }
        default:
    {
        displayBelowMap("不合理的输入");
        break;
    }
    }
    pos[dx][dy] = '*';
    return true;
}
void Map::showMenu()
{
    cout << "您目前的位置是：" << mapName[position] << endl;
    cout << "1.按回车进入区域。" << '\n';
    cout << "2.输入'v'保存游戏进度。" <<'\n';
    cout << "3.输入'wasd'以移动。" << '\n';
    cout << "4.ctrl-c 退出。" << '\n';
    cout << endl;
}
