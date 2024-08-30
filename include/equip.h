#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <functional>
//#include"../../include/combat.h"
#include <string>
#include <utility>
#include <vector>
#include <array>
#include <memory>




class BaseEquip{//物品基类 包括装备和药水
    public:
        std::string name;
        bool operator== (const BaseEquip& other) const;//用于哈希表
};

class Equip;


struct eqOnObj
{
    bool operator() (std::shared_ptr<BaseEquip> const a,std::shared_ptr<BaseEquip> const b) const
    {
        return *a == *b;
    }
};


struct hashBaseEquip{
    size_t operator()(const std::shared_ptr<BaseEquip> value) const;
};  

enum EquipTyp{//装备类型编号 同类型的编号相同
    tEquip,    
    tSword,
    tArmhour,
    tShoes,
};
static constexpr size_t EquipTypCount = 4;//武器装备栏长度

class Hero;




class Equip: public BaseEquip{//装备基类
    public:
        Equip();

        Equip(double hp,double mp,double def,double value);
        double hp = 0;
        double mp = 0;
        double def = 0;
        double value = 0;
        operator bool();//判断是否为空装备
        virtual EquipTyp typ();//获取当前装备的编号
        virtual void equiped(Hero& hero);//角色穿上装备
        virtual void takeoff(Hero& hero);//角色脱下装备
};


class Medicine: public BaseEquip
{
    public:
        Medicine();
        double hp;
        double mp;
        double atk;
        double def;
        double value;
        void used(Hero& hero,int n);//角色使用药水
        virtual void display();
};


class Bag;
class Store{
    public:
        Store(std::vector<std::shared_ptr<Equip>> equipstore = {},std::vector<std::shared_ptr<Medicine>> medicinestore = {});
        //void refresh();
        void display() const;
        void sold(std::shared_ptr<Equip> equip, int n,Bag& bag,Hero& hero);//角色买装备，商店卖装备
        void sold(std::shared_ptr<Medicine> medicine, int n,Bag& bag,Hero& hero);///角色买药水，商店卖药水
        void buy(std::shared_ptr<Equip> equip, int n,Bag& bag,Hero& hero);//角色卖装备，商店买
        void buy(std::shared_ptr<Medicine> medicine, int n,Bag& bag,Hero& hero);//角色卖药水
    private:
        std::unordered_map<std::shared_ptr<Equip>,int, hashBaseEquip, eqOnObj> equipcommodities;//商店的装备
        std::unordered_map<std::shared_ptr<Medicine>,int,hashBaseEquip, eqOnObj> medicinecommodities;//商店的药水
};






class Sword : public Equip
{
    public:
        friend class Bag;
        friend class Hero;
        Sword(double hp,double mp,double def,double value,double atk);
        double atk;
        EquipTyp typ();
        void equiped(Hero& hero);//角色穿上装备
        void takeoff(Hero& hero);//角色脱下装备
};

class StoneSword : public Sword
{
    public:
        friend class Bag;
        StoneSword(double hp,double mp,double def,double value,double atk);
};

class BronzeSword : public Sword
{
    public:
        friend class Bag;
        BronzeSword(double hp,double mp,double def,double value,double atk);
};

class IronSword : public Sword
{
    public:
        friend class Bag;
        IronSword(double hp,double mp,double def,double value,double atk);
};

class Armhour :public Equip
{
    public:
        friend class Bag;
        Armhour(int hp,int mp,int def,double value);
        EquipTyp typ();
        void equiped(Hero& hero);//角色穿上装备
        void takeoff(Hero& hero);//角色脱下装备
};



class Shoes :public Equip
{
    public:
        friend class Bag;
        Shoes(int hp,int mp,int def,double value);
        EquipTyp typ();
        void equiped(Hero& hero);
        void takeoff(Hero& hero);
};


class RedMedicine : public Medicine
{
    public:
        RedMedicine();
        void display() const;
};

class BlueMedicine : public Medicine
{
    public:
        friend class Hero;
        BlueMedicine();
        void display() const;
}; 



class Bag{
    public:
        friend class Hero;
        friend class Store;
        friend class Equip;
        void get(std::shared_ptr<Equip> equip, int n);//角色获得装备
        void get(std::shared_ptr<Medicine> Medicine, int n);//角色获得药水
        void display() const;
        void use(std::shared_ptr<Medicine> medicine,int n,Hero& hero);//角色使用药水
        void changeequip(std::shared_ptr<Equip> equip,Hero& hero);//角色更换装备
    private:
        std::unordered_map<std::shared_ptr<Equip>,int, hashBaseEquip, eqOnObj> bag;//未装备的装备
        std::unordered_map<std::shared_ptr<Medicine>,int, hashBaseEquip, eqOnObj> medicinebag;//药水
        std::array<std::shared_ptr<Equip>, EquipTypCount> equipbag;//已装备的装备 武器栏
        //Equip  equipbag[EquipTypCount] ;
};

class Skill
{
public:
	Skill();
	Skill(std::string name, std::string introduce, int harm, int magicLose);
	~Skill();
	void showSkill();
	std::string getName();
	std::string getIntroduce();
	int getHarm();
	int getMagicLose();
private:
	std::string name;//名称
	std::string introduce;//介绍
	int harm;//伤害
	int magicLose;//耗蓝
};

class Bag;
class Hero
{
	friend class RedMedicine;
    friend class BlueMedicine;
    friend class Sword;
    friend class Armhour;
    friend class Shoes;
    friend class Medicine;
	friend class Bag;
public:
	Hero();
	~Hero();
	void setName();
	void showHero();
	void addHp(int num);//增加生命上限
	void adjustHp(int num);//增加或减少生命值
	void addMp(int num);//增加魔法上限
	void adjustMp(int num);//增加或减少魔法值
	void adjustAttack(int num);//增加或减少攻击
	void adjustDefend(int num);//增加或减少防御
	void addExp(int num);//增加或减少经验
	void adjustGold(int num);//增加或减少金币
	int getHp();
	int getMp();
	int getAttack();
	int getDefend();
	int getExp();
	int getGold();
	int getLevel();
	Bag& getBag();
	std::unordered_map<std::shared_ptr<Medicine>,int, hashBaseEquip, eqOnObj>& getMedicine();
	void setSkill(Skill skill);
	std::vector<Skill>& getskills();
	void use(std::shared_ptr<Medicine> medicine, int n);
    //void changeequip(std::shared_ptr<Equip> equip);
private:
	std::string name;
	int hp;//血量
	int hpMax;
	int mp;//蓝量
	int mpMax;
	int attack;
	int defend;
	int exp;
	int expMax[10] = { 10,50,150,500,1000,2000,4000,8000,15000,30000 };
	int level;
	int gold;
	std::vector<Skill> skills;
	int skillNumber;//技能最大数目；
	Bag bag;
};


/*
class Hero
{
    friend class RedMedicine;
    friend class BlueMedicine;
    friend class Sword;
    friend class Armhour;
    friend class Shoes;
    friend class Medicine;
    public:        
        void display() const
        {
            std::cout << hpMax<<" "<< hp <<" "<< mpMax <<" "<<mp<<" " << attack << " "<< defend << std::endl;
        }
        void fun(){
            hp -= 50;
            mp -= 50;
        }
    private:
        double hp=100;
        double hpMax=100;
        double mp=100;
        double mpMax=100;
        double attack=10;
        double defend=10;
        double skills;
        double stuffs;
};*/
