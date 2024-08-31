#include "../../include/map.h"
#include "../../include/combat.h"
#include "../../include/equip.h"
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
char mapName[11][50] = {"卧龙山", "祸窟", "地宫", "北阳山", "藏经阁", "郊外", "锻造屋", "中央主城", "药铺", "道远村", "郊外"};

static void CannotMove()
{
    cout << "无法移动" << endl;
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
        while (!enemyNum)
        {
            srand(time(NULL));
            enemyNum = rand() % 4;
        }
        for (int i = 0; i < enemyNum; i++)
        {
            srand(time(NULL));
            int randomNum = rand() % 7;
            if (randomNum == 0 && posR[0][0] != '#')
            {
                posR[0][0] = '#';
                break;
            }
            if (randomNum == 0 && posR[0][0] == '#')
            {
                randomNum++;
            }

            if (randomNum == 1 && posR[0][1] != '#')
            {
                posR[0][1] = '#';
                break;
            }
            if (randomNum == 1 && posR[0][1] == '#')
            {
                randomNum++;
            }
            if (randomNum == 2 && posR[0][2] != '#')
            {
                posR[0][2] = '#';
                break;
            }
            if (randomNum == 2 && posR[0][2] == '#')
            {
                randomNum++;
            }
            if (randomNum == 3 && posR[1][0] != '#')
            {
                posR[1][0] = '#';
                break;
            }
            if (randomNum == 3 && posR[1][0] == '#')
            {
                randomNum++;
            }
            if (randomNum == 4 && posR[1][2] != '#')
            {
                posR[1][2] = '#';
                break;
            }
            if (randomNum == 4 && posR[1][2] == '#')
            {
                randomNum++;
            }
            if (randomNum == 5 && posR[2][0] != '#')
            {
                posR[2][0] = '#';
                break;
            }
            if (randomNum == 5 && posR[2][0] == '#')
            {
                randomNum++;
            }
            if (randomNum == 6 && posR[2][1] != '#')
            {
                posR[2][1] = '#';
                break;
            }
            if (randomNum == 6 && posR[2][1] == '#')
            {
                randomNum++;
            }
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
    cout << "'&':移动至此可退出地图" << '\n';
    switch (position)
    {
    case 4:
    {
        cout << " '#':移动至此可学习技能" << '\n';
        break;
    }
    case 6:
    {
        cout << "'#':移动至此可打造你的装备" << '\n';
        break;
    }
    case 7:
    {
        cout << "'#':移动至此可购买物品" << '\n';
        break;
    }
    case 8:
    {
        cout << "'#':移动至此可治疗和制造药品" << '\n';
        break;
    }
    case 1:
    {
        cout << "'#'处可与怪物战斗" << '\n';
        break;
    }
    case 2:
    {
        cout << "'#':移动至此可与怪物战斗" << '\n';
        break;
    }
    case 3:
    {
        cout << "'#':移动至此可与怪物战斗" << '\n';
        break;
    }
    case 9:
    {
        cout << "'#':移动至此可与怪物战斗" << '\n';
        break;
    }

    default:
        break;
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
                if (position == 8)
                {
                    store.trade(h.getBag(),h);
                }
            }
            else if ((position == 1 || position == 3 || position == 2 || position == 9) && posR[temp][dy] == '#')
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
                cout << "这里有对话" << endl;
                if (position == 8)
                {         
                    store.trade(h.getBag(),h);
                }
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
            else if ((position == 1 || position == 3 || position == 2 || position == 9) && posR[dx][temp] == '#')
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
                if ((posR[i][j]) != '#' && (posR[i][j]) != '&')
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
    std::shared_ptr<StoneSword> a = std::make_shared<StoneSword> (0,0,0,10,10);
    std::shared_ptr<IronSword> b = std::make_shared<IronSword> (0,0,0,30,30);
    std::shared_ptr<BronzeSword> c= std::make_shared<BronzeSword> (0,0,0,20,20);
    std::shared_ptr<Shoes> d = std::make_shared<Shoes> (5,5,5,10);
    std::shared_ptr<Armhour> e = std::make_shared<Armhour> (10,10,20,30);
    std::vector<std::shared_ptr<Equip>> equipstore = {a,b,c};
    std::vector<std::shared_ptr<Medicine>> medicinestore = {redMedicine,bluemedicine};
    Store store(equipstore,medicinestore);
    h.setSkill(s2);
    position = p;

    if (p == 0)
    {
        dx = 2;
        dy = 0;
    }
    if (p == 1)
    {
        dx = 2;
        dy = 1;
    }
    if (p == 2)
    {
        dx = 0;
        dy = 2;
    }
    if (p == 3)
    {
        dx = 1;
        dy = 2;
    }
    if (p == 4)
    {
        dx = 2;
        dy = 2;
    }
    if (p == 5)
    {
        dx = 3;
        dy = 2;
    }
    if (p == 6)
    {
        dx = 1;
        dy = 3;
    }
    if (p == 7)
    {
        dx = 2;
        dy = 3;
    }
    if (p == 8)
    {
        dx = 2;
        dy = 4;
    }
    if (p == 9)
    {
        dx = 2;
        dy = 5;
    }

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
    // eraseScreen();
    setCursorPos(0, 0);
    cout << "世界地图:" << '\n';
    cout << "                        __________" << '\n';
    cout << "                       |          |" << '\n';
    cout << "                       |   卧龙山 |" << '\n';
    cout << "                       |   " << pos[2][0] << "      |" << '\n';
    cout << "                       |__________|" << '\n';
    cout << "                       |          |" << '\n';
    cout << "                       |   祸窟   |" << '\n';
    cout << "                       |     " << pos[2][1] << "    |" << '\n';
    cout << "_______________________|__________|__________" << '\n';
    cout << "|          |          |           |          |" << '\n';
    cout << "|   地宫   |   北阳山 |   藏经阁  |   郊外   |" << '\n';
    cout << "|    " << pos[0][2] << "     |     " << pos[1][2] << "    |     " << pos[2][2] << "     |    " << pos[3][2] << "     |" << '\n';
    cout << "|__________|__________|___________|__________|" << '\n';
    cout << "           |          |          |          |" << '\n';
    cout << "           |   锻造屋 | 中央主城 |   药铺   |" << '\n';
    cout << "           |     " << pos[1][3] << "    |      " << pos[2][3] << "   |    " << pos[3][3] << "     |" << '\n';
    cout << "           |__________|__________|__________|" << '\n';
    cout << "                      |          |" << '\n';
    cout << "                      |   道远村 |" << '\n';
    cout << "                      |    " << pos[2][4] << "     |" << '\n';
    cout << "                      |__________|" << '\n';
    cout << "                      |          |" << '\n';
    cout << "                      |    郊外  |" << '\n';
    cout << "                      |    " << pos[2][5] << "     |" << '\n';
    cout << "                      |__________|" << '\n';
    cout.flush();
}

void Map::action()
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
            cout << "移动失败" << endl;
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
            cout << "移动失败" << '\n';
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
    case 'n':
    {
        cout << "输入的是i" << endl;
        break;
    }

    case 'm':
    {
        Room myRoom = Room(h,store, position);
        myRoom.showRoom();
        myRoom.actionRoom();
        break;
    }
    case 'v':
    {
        cout << "游戏进度已保存。" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::sleep(5);
        auto save = hps::to_string(*this);
        
        break;
    }
    

        default:
    {
        cout << "不合理的输入" << endl;
        break;
    }
    }
    pos[dx][dy] = '*';
}
void Map::showMenu()
{
    cout << "您目前的位置是：" << mapName[position] << endl;
    cout << "1.输入'm'进入区域。" << '\n';
    cout << "2.输入'v'保存游戏进度。" <<'\n';
    cout << "3.输入'wasd'以移动。" << endl;
    
}
