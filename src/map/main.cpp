
#include "../../include/map.h"

>>>>>>> 4d63a353fa461beeb4c9a572b521f45e4ca0cd18

using namespace std;


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


    Map::Map(int p = 7)
    {
        position = p;
        
        if (p == 0){
            dx = 2;
            dy = 0;
        }
        if (p == 1){
            dx = 2;
            dy = 1;
        }
        if (p == 2){
            dx = 0;
            dy = 2;
        }
        if (p == 3){
            dx = 1;
            dy = 2;
        }
        if (p == 4){
            dx = 2;
            dy = 2;
        }
        if (p == 5){
            dx = 3;
            dy = 2;
        }
        if (p == 6){
            dx = 1;
            dy = 3;
        }
        if (p == 7){
            dx = 2;
            dy = 3;
        }
        if ( p == 8){
            dx = 2;
            dy = 4;
        }
        if (p == 9){
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
    void Map::showMap(){
    cout << "世界地图:" << endl;
	cout<<"                        __________"<<endl;
	cout<<"                       |          |"<<endl;
	cout<<"                       |   卧龙山 |"<<endl;
    cout << "                       |   " << pos[2][0] << "      |" << endl;
    cout<<"                       |__________|"<<endl;
	cout<<"                       |          |"<<endl;
	cout<<"                       |   祸窟   |"<<endl;
    cout << "                       |     " << pos[2][1] << "    |" << endl;
    cout<<"_______________________|__________|__________"<<endl;
	cout<<"|          |          |           |          |"<<endl;
	cout<<"|   地宫   |   北阳山 |   藏经阁  |   郊外   |"<<endl;
    cout << "|    " << pos[0][2] << "     |     " << pos[1][2] << "    |     "<< pos[2][2] << "     |    " << pos[3][2] << "     |" << endl;
    cout<<"|__________|__________|___________|__________|"<<endl;
    cout << "           |          |          |          |" << endl;
    cout<<"           |   锻造屋 | 中央主城 |   药铺   |"<<endl;
    cout << "           |     " << pos[1][3] << "    |      " << pos[2][3] << "   |    " << pos[3][3] << "     |" << endl;
    cout<<"           |__________|__________|__________|"<<endl;
	cout<<"                      |          |"<<endl;
	cout<<"                      |   道远村 |"<<endl;
    cout<<"                      |    "<< pos[2][4] <<"     |"<<endl;
	cout<<"                      |__________|"<<endl;
	cout<<"                      |          |"<<endl;
	cout<<"                      |    郊外  |"<<endl;
    cout<<"                      |    "<< pos[2][5] <<"     |"<<endl;
	cout<<"                      |__________|"<<endl;
    }
    

    void Map::showPosition(){
        cout << "您目前的位置是：" << mapName[position] << endl;
    }
    void Map::move(){
        char command;
        cout << "输入wasd以移动" << endl;
        cin >> command;
        pos[dx][dy] = ' ';
        switch (command){
        case 'w':{
            if (position == 0 || position == 2 || position == 3 || position == 5){
                cout << "移动失败" << endl;
                break;
            }
            if (position == 1 || position == 10)
            {
                dy--;
                position -= 1;
                break;
            }
            if (position == 4 || position == 6 || position == 7 || position == 8){
                dy--;
                position -= 3;
                break;
            }
            if (position == 9){
                dy--;
                position -= 2;
                break;
            }
            break;
        }
        case 'a':{
            if (position == 2 || position == 0 || position == 1 || position == 6 || position == 9 || position == 10)
                {
                    cout << "移动失败" << endl;
                    break;
                }
                if (position == 3 || position == 4 || position == 5 || position == 7 || position == 8){
                    dx--;
                    position--;
                }
                break;
        }
        case 'd':{
            if (position == 1 || position == 5 || position == 8 || position == 9 || position == 10 || position == 0)
            {
                cout << "无法移动" << endl;
            }
            if (position == 2 || position == 3 || position == 4 || position == 6 || position == 7){
                dx++;
                position++;
            }
            break;
        }
        case 's':{
            if (position == 2 || position == 6 || position == 10 || position == 8){
                cout << "无法移动" << endl;
                break;
            }
            if (position == 3 || position == 4 || position == 5 || position == 1){
                dy++;
                position += 3;
                break;
            }
            if (position == 7){
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
            
    
        }
        default:
            break;
        }
        pos[dx][dy] = '*';
        
    }
        
//     Map(){
// 	position = 0;
// 	dx = 5;
// 	dy = 2;

// 	for (int i = 0; i < 6; i++)
// 	{
// 		for (int j = 0; j < 6; j++)
// 		{
// 			pos[i][j] = ' ';
// 		}
// 	}
// 	pos[dx][dy] = '*';
// }
    bool Map::isCombat(){
        if (position == 0 || position == 1 || position == 2 || position == 3 || position == 9){
            return true;
        }
        else
            return false;
    }
    bool Map::isChat(){
        if (position == 4 || position == 6 || position == 8){
            return true;
        }
        else
            return false;
    }

    int Map::getPostion(){
        return position;
    }
    string Map::getName(){
        return mapName[position];
    }

    

