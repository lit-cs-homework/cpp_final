
#include "../../include/map.h"

using namespace std;


class Enemy{
public:
    string getname(){
        return name;
    }
    int gettype(){
        return type;
    }
    int gethealth(){
        return health;
    }
    int getattack(){
        return attackNum;
    }
    int getdefend(){
        return defend;
    }
    int getawards(){
        return awards;
    }
private:
    string name;
    int type;
    int health;
    int attackNum;
    int defendNum;
    string awards;
};

class Hero{
public:
    string getname(){
        return name;
    }
    string getgender(){
        return gender;
    }
    int gethealth(){
        return health;
    }
    int getmagic(){
        return magic;
    }
    int getattack(){
        return attack;
    }
    int getdefend(){
        return defend;
    }
    int getexp(){
        return exp;
    }
    int getlevel(){
        return level;
    }
    int getmoney(){
        return money;
    }

private:
    string name;
    char gender;
    int health;
    int magic;
    int attack;
    int defend;
    int exp;
    int level;
    int money;
};

class Map{
public:
    Map(){}
    void showMap(){
    cout << "世界地图:" << endl;
	cout<<"                        __________"<<endl;
	cout<<"                       |          |"<<endl;
	cout<<"                       |   卧龙山  |"<<endl;
	cout<<"                       |__________|"<<endl;
	cout<<"                       |          |"<<endl;
	cout<<"                       |   祸窟   |"<<endl;
	cout<<"_______________________|__________|_________|"<<endl;
	cout<<"|          |          |           |          |"<<endl;
	cout<<"|   地宫   |   北阳山  |   藏经阁  |   郊外    |"<<endl;
	cout<<"|__________|__________|___________|__________|"<<endl;
    cout << "         |          |          |          |" << endl;
    cout<<"           |   锻造屋  |  中央主城 |   药铺  |"<<endl;
	cout<<"           |__________|__________|__________|"<<endl;
	cout<<"                      |          |"<<endl;
	cout<<"                      |   道远村  |"<<endl;
	cout<<"                      |__________|"<<endl;
	cout<<"                      |          |"<<endl;
	cout<<"                      |    郊外  |"<<endl;
	cout<<"                      |__________|"<<endl;
    }

    void showPosition(){
        cout << "您目前的位置是：" << "中央主城" << endl;
    }
};

class Scene{
private:
    string name;
    char type;
public:
    void move(){

    }
};
class Scene1:public Scene{
public:
    Scene1(string name):Scene(name){

    }
    void showMenu(){
        cout << "菜单"<<endl;
        cout << "1.继续前进" << endl;
        cout << "2.与npc交谈" << endl;
    }
};

/*class Scene2:Scene{
    void showmenu(){
        cout << "菜单" << endl;
        cout << "1.继续前进" << endl;
        cout << "2.战斗" << endl;
    }
};*/

int main(){
    Scene1 city("中央主城");
    Map myMap();
    myMap.showMap();
    myMap.showPosition();
    city.showMenu();
}