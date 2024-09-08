#include "../../include/map.h"
#include "../../include/combat.h"
#include "../../include/equip.h"
#include <cstdlib>
#include <string>
#include <array>
#include <cassert>
#include "../../include/scenario.h"

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

#define mapPlacesNumber 11
#define MaxMapNameLen 12   // len*3, where len is 4

using MapNameArray = std::array<std::string, mapPlacesNumber>;

// Python's str.center like
// assert minWidth > 0;
// assert s consist 3-byte unicode (utf-8's chinese)
// assume one char is full-width when rendered.
static
std::string center(const std::string& s, int minFontWidth) {
    assert(minFontWidth > 0);
    auto sFontWidth = s.size() / 3;
    assert(sFontWidth*3 == s.size());
    int delta = minFontWidth - sFontWidth;
    if (delta <= 0) {
        return s;
    }

    auto truncHalfInt = delta / 2;
    std::string prefix, suffix;
    const char *fill = "  ";
#define loop(N) for (size_t i = 0; i < (N); i++)
    loop(truncHalfInt) prefix += fill;
    loop(delta - truncHalfInt) suffix += fill;
    if (delta % 2 == 1) {
        prefix += ' ';
        suffix.resize(suffix.size() - 1);
    }
    return prefix + s + suffix;
#undef loop
}
#define _(s)  (center((s), 5))

static
MapNameArray mapName = {
    _("鬼门"   ),
    _("祸窟"     ),
    _("地宫"     ),
    _("地窖"   ),
    _("地道"   ),
    _("暗室"     ),
    _("石窟"   ),
    _("岩穴" ),
    _("穴口"     ),
    _("地牢"   ),
    _("冥界"     )
};

#undef _

//std::string mapName[mapPlacesNumber] = {"  卧龙山  ", "   祸窟   ", "   地宫   ", "  北阳山  ", "  藏经阁  ", "   郊外   ", "  锻造屋  ", " 中央主城 ", "   药铺   ", "  道远村  ", "   郊外   "};


static
void arrangeMapName(MapNameArray& mapName){
    // for (int i = 0; i < 11; i++) {
    //     std::string tempname = mapName[i];
    //     int length = tempname.length();
    //         tempname += std::string(4 - length, ' ');
    //         tempname.insert(length / 2, ' ');
    //     mapName[i] = tempname.c_str();
    // }
    for(auto& i: mapName) {
        assert(i.size() <= MaxMapNameLen);
        i = center(i, MaxMapNameLen);
    }

}

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
Room::Room(Hero &hm,Store& storem, Scenario& scm, int p):h(hm),store(storem),sc(scm)
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
    createEnemy(position,1,1);
    updateAffair(position);
}

void Room::roomBattle(int pos)
{
    switch(pos)
    {
        case 1:
        {
            fightDenOfDisaster(&h);
            break;
        }
        case 3:
        {
            fightCellar(&h);
            break;
        }
        case 4:
        {
            fightTunnel(&h);
            break;
        }
        case 6:
        {
            fightGrottoes(&h);
            break;
        }
        case 9:
        {
            fightDungeon(&h);
            break;
        }
    }
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
    cout << " * :当前你的位置"<<endl;
    cout << "'&':移动至此可退出地图" << '\n';
    switch (position)
    {
    case 1:
    case 3:
    case 4:
    case 6:
    case 9:
    {
        cout << "'!':移动至此可与怪物战斗" << '\n';
    }
    case 7:
    case 0:
    case 2:
    case 5:
    case 10:
    {
        cout << "'#':移动至此可触发事件。" << '\n';
        break;
    }

    default:
        break;
    }
}

void Room::communciateNpc(int position){
    switch(position){
        case 0:{
            sc.ghostdom();
            ms_sleep(700);
            break;
        }
        case 1:{
            sc.DenOfDisaster();
            ms_sleep(700);
            break;
        }
        case 2:{
            sc.underPalace();
            ms_sleep(700);
            break;
        }
        case 3:{
            sc.Cellar();
            ms_sleep(700);
            break;
        }
        case 4:{
            sc.Tunnel();
            ms_sleep(700);
            break;
        }
        case 5:{
            sc.darkroom();
            ms_sleep(700);
            break;
        }
        case 7:{
            sc.Cave();
            break;
        }
        case 6:{
            sc.Grottoes();
            ms_sleep(700);
            break;
        }
        case 9:{
            sc.Dungeon();
            ms_sleep(700);
            break;
        }
        case 10:{
            sc.SweatPore();
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
            else if (positionR == 3 && posR[temp][dy] == '#')
            {
                if(position != 8)
                {
                    communciateNpc(position);
                    updateAffair(position);
                }
            }
            else if ((position == 1 || position == 3 || position == 4 || position == 6 ||position == 9) && posR[temp][dy] == '!')
            {
                eraseScreen();
                roomBattle(position);
                positionR -= 3;
                dx--;
                createEnemy(position,dx,dy);
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
            else if (positionR == 1 && posR[dx][temp] == '#')
            {
                if(position != 8)
                {
                    communciateNpc(position);
                    updateAffair(position);
                }
            }
            else if ((position == 1 || position == 3 || position == 4 || position == 6 ||position == 9) && posR[dx][temp] == '!')
            {
                eraseScreen();
                roomBattle(position);
                positionR--;
                dy--;
                createEnemy(position,dx,dy);
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
            else if ((position == 1 || position == 3 || position == 4 || position == 4 ||position == 9) && posR[dx][temp] == '!')
            {
                eraseScreen();
                roomBattle(position);
                positionR++;
                dy++;
                createEnemy(position,dx,dy);
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
            else if ((position == 1 || position == 3 || position == 4 || position == 6 ||position == 9) && posR[temp][dy] == '!')
            {
                eraseScreen();
                roomBattle(position);
                dx++;
                positionR += 3;
                createEnemy(position,dx,dy);
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

void Room::createEnemy(int position, int dx, int dy)
{
    switch(position)
    {
        case 1:
        case 3:
        case 4:
        case 6:
        case 9:
        {
            int num1=rand()%3;
            int num2=rand()%3;
            while((num1 == 0 && num2 == 0)||(num1 == 2 && num2 == 2)||(num1 == dx && num2 == dy))
            {
                num1=rand()%3;
                num2=rand()%3;
            }
            posR[num1][num2]='!';
        }
    }
}
void Room::updateAffair(int position)
{
    switch(position)
    {
         case 0:
        {
            if(sc.getScenario() == 12)
            {
                posR[0][0] = '#';
            }
            else
            {
                posR[0][0] = ' ';
            }
             break;
        }
        case 1:
        {
            if(sc.getScenario() == 3)
            {
                posR[0][0] = '#';
            }
            else
            {
                posR[0][0] = ' ';
            }
             break;
        }
        case 3:
        {
            if(sc.getScenario() >=2 && sc.getScenario() <= 4)
            {
                posR[0][0] = '#';
            }
            else
            {
                posR[0][0] = ' ';
            }
             break;
        }
        case 4:
        {
            if(sc.getScenario() == 1)
            {
                posR[0][0] = '#';
            }
            else
            {
                posR[0][0] = ' ';
            }
             break;
        }
        case 6:
        {
            if(sc.getScenario() >=5 && sc.getScenario() <= 9)
            {
                posR[0][0] = '#';
            }
            else
            {
                posR[0][0] = ' ';
            }
             break;
        }
        case 9:
        {
            if(sc.getScenario() >=7 && sc.getScenario() <= 8)
            {
                posR[0][0] = '#';
            }
            else
            {
                posR[0][0] = ' ';
            }
             break;
        }
        case 7:
        {
            if(sc.getScenario() <= 6)
            {
                posR[0][0] = '#';
            }
            else
            {
                posR[0][0] = ' ';
            }
             break;
        }
        case 2:
        {
            if(sc.getScenario() <= 8)
            {
                posR[0][0] = '#';
            }
            else
            {
                posR[0][0] = ' ';
            }
             break;
        }
        case 5:
        {
            if(sc.getScenario() == 12)
            {
                posR[0][0] = '#';
            }
            else
            {
                posR[0][0] = ' ';
            }
             break;
        }
        case 10:
        {
            if(sc.getScenario() <= 10)
            {
                posR[0][0] = '#';
            }
            else
            {
                posR[0][0] = ' ';
            }
            break;
        }
    }
}
Map::Map(int p /*=7*/): sc(h,store), backup(Backup::Cwd())
{
    if(backup.hasData()) {
        backup.tryLoad(*this); // discard result
    } else {

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
     }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            pos[i][j] = ' ';
        }
    }
    pos[dx][dy] = '*';
    sc.Cave();
    Room myRoom(h,store, sc, position);
    myRoom.showRoom();
    myRoom.actionRoom();
    
}

void Map::showMap()
{
    eraseScreen();
    setCursorPos(0, 0);
    cout << "世界地图:" << '\n';
    cout << "                       __________" << '\n';
    cout << "                      |          |" << '\n';
    cout << "                      |"<<mapName[0]<<"|" << '\n';
    cout << "                      |    " << pos[2][0] << "     |" << '\n';
    cout << "                      |__________|" << '\n';
    cout << "                      |          |" << '\n';
    cout << "                      |"<<mapName[1]<<"|" << '\n';
    cout << "                      |    " << pos[2][1] << "     |" << '\n';
    cout << "______________________|__________|___________" << '\n';
    cout << "|          |          |          |          |" << '\n';
    cout << "|"<<mapName[2]<<"|"<<mapName[3]<<"|"<<mapName[4]<<"|"<<mapName[5]<<"|" << '\n';
    cout << "|    " << pos[0][2] << "     |    " << pos[1][2] << "     |    " << pos[2][2] << "     |    " << pos[3][2] << "     |" << '\n';
    cout << "|__________|__________|__________|__________|" << '\n';
    cout << "           |          |          |          |" << '\n';
    cout << "           |"<<mapName[6]<<"|"<<mapName[7]<<"|"<<mapName[8]<<"|" << '\n';
    cout << "           |    " << pos[1][3] << "     |    " << pos[2][3] << "     |    " << pos[3][3] << "     |" << '\n';
    cout << "           |__________|__________|__________|" << '\n';
    cout << "                      |          |" << '\n';
    cout << "                      |"<<mapName[9]<<"|" << '\n';
    cout << "                      |    " << pos[2][4] << "     |" << '\n';
    cout << "                      |__________|" << '\n';
    cout << "                      |          |" << '\n';
    cout << "                      |"<<mapName[10]<<"|" << '\n';
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
        if(position == 1 && sc.getScenario() <= 10)
        {
            narration("一个法阵挡在路前，无法通过。");
            ms_sleep(1000);
            break;
        }
        if(position == 1 && sc.getScenario() ==11)
        {
            narration("你使用冥界之石破除了法阵。");
            ms_sleep(1000);
            sc.adjustScenario(12);
        }
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
        if(position == 3 && sc.getScenario() <= 4)
        {
            narration("尘封的大门，已经被一把大锁锁住了。");
            ms_sleep(1000);
            break;
        }
        if(position == 3 && sc.getScenario() >= 5 &&sc.getScenario() <= 8)
        {
            narration("大锁不知何时已经被打开。");
            ms_sleep(1000);
        }
        if(position == 3 && sc.getScenario() >= 9)
        {
            narration("不只是锁，连门都已被破开。里面已经什么都没有了。");
            ms_sleep(1000);
        }
        if(position == 7 && sc.getScenario() <= 4)
        {
            narration("一堆黑石挡住了去路");
            ms_sleep(1000);
            break;
        }
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
        if(position == 4 && sc.getScenario() <= 11)
        {
            narration("地图上标出了这个地方但是却没有路可走。");
            ms_sleep(1000);
            break;
        }
        if(position == 4 && sc.getScenario() ==12)
        {
            narration("你来到一处墙角，手握剑柄释出全力，墙壁破开，露出了通道。");
            ms_sleep(1000);
        }
        if(position == 4 && sc.getScenario() == 13)
        {
            narration("里面还有一下微弱的声音，但现在要紧的事是前往穴口。");
            ms_sleep(1000);
            break;
        }
        if(position == 7 && sc.getScenario() <= 12)
        {
            narration("地图上标出了这个地方但是却没有路可走。");
            ms_sleep(1000);
            break;
        }
        if(position == 7 && sc.getScenario() == 13)
        {
            sc.end();
            break;
        }
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
        if(position == 5)
        {
            narration("这里没有路可走。");
            ms_sleep(1000);
            break;
        }
         if(position == 9)
        {
            narration("墙面上刻有歪七扭八的字迹：欲入冥界，必先做好死的准备！");
            ms_sleep(1000);
        }
        if(position == 7 && sc.getScenario() <=6)
        {
            npcTalk("邓锋魄的声音从后面传来：劝你别去，地牢里的怪物可不像地道里的那样简单！");    
            narration("你想了想，还是停下了脚步。");
            ms_sleep(1000);
            break;
        }
        if(position == 3 && sc.getScenario()<=4)
        {
            narration("一堆黑石挡住了去路");
            ms_sleep(1000);
            break;
        }
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
        Room myRoom(h,store, sc, position);
        myRoom.showRoom();
        myRoom.actionRoom();
        break;
    }
    case 'v':
    {
        backup.save(*this);
        displayBelowMap("游戏进度已保存。");
        
        
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