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
    _("卧龙山"   ),
    _("祸窟"     ),
    _("地宫"     ),
    _("北阳山"   ),
    _("藏经阁"   ),
    _("郊外"     ),
    _("锻造屋"   ),
    _("中央主城" ),
    _("药铺"     ),
    _("道远村"   ),
    _("郊外"     )
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
        // 7 as there're 7 places in the map
#define randMapPos() (rand() % 7)
        while (!enemyNum)
        {
            srand(time(NULL));
            enemyNum = rand() % 4;
        }
        switch (enemyNum){
            case 1:{
                randomNum1 = randMapPos();
                break;
            }
            case 2:{
                randomNum1 = randMapPos();
                randomNum2 = randMapPos();
                break;
            }
            case 3:{
                randomNum1 = randMapPos();
                randomNum2 = randMapPos();
                randomNum3 = randMapPos();
            }
               
            
        }   
            while(randomNum1==randomNum2){
                randomNum1 = randMapPos();
            }
            while (randomNum2 == randomNum3){
                randomNum2 == randMapPos();
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
#undef randMapPos
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
                fightTunnel(&h);
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
                fightTunnel(&h);
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
                fightTunnel(&h);
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
                fightTunnel(&h);
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

Map::Map(int p /*=7*/): sc(h)
{

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
        if(position == 1 && sc.getScenario()<=9)
        {
            narration("一个法阵挡在路前，无法通过。");
            break;
        }
        if(position == 1 && sc.getScenario() ==10)
        {
            narration("你使用冥界之石破除了法阵。");
            sc.adjustScenario(11);
            break;
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
        if(position == 3 && sc.getScenario()<=4)
        {
            narration("尘封的大门，已经被一把大锁锁住了。");
            break;
        }
        if(position == 7 && sc.getScenario()<=4)
        {
            narration("一堆黑石挡住了去路");
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
        if(position == 4 && sc.getScenario() <= 10)
        {
            narration("地图上标出了这个地方但是却没有路可走。");
            break;
        }
        if(position == 4 && sc.getScenario() ==11)
        {
            narration("你来到一处墙角，手握剑柄释出全力，墙壁破开，露出了通道。");
            sc.adjustScenario(12);
            break;
        }
        if(position == 4 && sc.getScenario() == 12)
        {
            narration("里面还有一下微弱的声音，但现在要紧的事是前往穴口。");
            break;
        }
        if(position == 7 && sc.getScenario() <= 11)
        {
            narration("地图上标出了这个地方但是却没有路可走。");
            break;
        }
        if(position == 7 && sc.getScenario() == 12)
        {
            narration("你来到了另一处墙角，一剑轰出，又是一条通道。你刚要进去，后面传来了熟悉的声音。");
            npcTalk("邓锋魄：真是太麻烦你了，还专门为我打通了一条出去的路。");
            heroTalk("你：你知道的，我从不为别人做事。");
            npcTalk("邓锋魄：我可不这么想。与地灵一战，你已经没多少剩余了吧？我一直存下的魂印都能成为我的助力，你不是我的对手。");
            heroTalk("你：你太自信了，之前和我还有那三巨头对抗你就没什么剩余了。为了防止引起地灵的注意你也不敢大肆屠杀魔物。就算你这段时间把所有人类都杀了，抢了他们身上的所有魂印。杀黑龙去无嗔戒的时候估计也没多少剩余了吧？");
            npcTalk("邓锋魄：那就来试试！我就不信...");
            ms_sleep(1000);
            heroTalk("你突然插口：你以为利用地牢的石碑能骗过我？");
            narration("邓锋魄的脸色闪过一丝慌乱。");
            heroTalk("你：我早就有疑问，我失忆之前为什么会把最多的信息放在最有可能遭破坏的石碑上？看来你有十足的把握，我被你清除的记忆绝对找不回来，这样我就能百分百相信已经被你修改过的内容。让我猜猜，和我打你会立刻示弱然后逃跑消去踪迹，等我进入穴口，然后就会被你这段时间花大代价设下的封印困住是吧？");
            ms_sleep(2000);      
            npcTalk("邓锋魄：你...");
            heroTalk("你：看来你是真的舍不得多花一点力量把石窟打开啊，不然要是石窟石碑也被修改了，我就真的要相信石碑说的话了。又或者说，你根本不敢去石窟，害怕引起黑龙的注意？想来你胆子也没有多大，连尝试吸收石碑下我的力量都不敢，看来是不愿冒一点险啊！");
            ms_sleep(2000);      
            heroTalk("你接着说：你料定我没能力在石窟石碑里刻下记忆。却没想到我留下的装备里恰好有一张地下的地图，里面根本没穴口这个地方！其实你不知道怎么样才能出去，你也不想出去，你只是觉得一直待在这个地方，你就可以获得越来越强大的力量，这样你迟早可以摆脱束缚。但我不一样，我是真受不了这个地方的味道了。");
            ms_sleep(2000);      
            npcTalk("邓锋魄：你要做什么？");
            heroTalk("你举起了鬼玺，高喊道：地灵，想必你也听到了吧！留你一命就是为了这个！我不在乎你最终能达到什么实力，我只想要自己能逃出去！现在，我可以让所有地下怪物全都自杀，你可以汲取到无穷的力量，足以让你恢复状态，然后杀了这个小人！以后你还能达成你的目的！你需要做的，就只是让我逃出去而已。否则，我会除了你的性命，成为地下新的主宰！");
            npcTalk("邓锋魄：等一下！地灵！千万别答应他！");
            narration("地下空间传了沉闷的回响，你的身后出现了一道漆黑的洞口。");
            narration("你迅速来到洞口前，控制一只影魔钻了进去，片刻后，影魔又出来了，身上遍布着黑痕，你一眼就认出是这属于阳光对影魔的伤害。");
            heroTalk("你再次举起鬼玺：杀害所有怪物的事情就交给锋魄兄弟了！");
            narration("地下空间里的怪物几乎全向岩穴涌了过去，向邓锋魄发起了攻击...");
            narration("群攻之下，邓锋魄只能边战边退，根本来不及收集魂印。而落到地上的魂印会被地灵吸收，届时邓锋魄无处可逃。");
            narration("你一剑将邓锋魄逼退，转身跳入黑洞。一眨眼，眼前便是磷光点点的树林，你一剑再出，黑洞瞬间崩溃。");
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
         if(position == 9)
        {
            narration("墙面上刻有歪七扭八的字迹：欲入冥界，必先做好死的准备！");
            break;
        }
        if(position == 7 && sc.getScenario() <=6)
        {
            npcTalk("邓锋魄的声音从后面传来：劝你别去，地牢里的怪物可不像地道里的那样简单！");    
            narration("你想了想，还是停下了脚步。");
            break;
        }
        if(position == 3 && sc.getScenario()<=4)
        {
            narration("一堆黑石挡住了去路");
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