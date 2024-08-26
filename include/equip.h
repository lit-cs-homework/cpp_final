#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include <string>
#include <utility>
#include <vector>

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
        float hp=100;
        float hpMax=100;
        float mp=100;
        float mpMax=100;
        float attack=10;
        float defend=10;
        float skills;
        float stuffs;
};

enum EquipTyp{
    tEquip,    
    tSword,
    tArmhour,
    tShoes,
};
static constexpr size_t EquipTypCount = 3;


class BaseEquip{
    public:
        std::string name;
        bool operator== (const BaseEquip& other)const{return name==other.name;}
};


class Equip: public BaseEquip{
    public:
        Equip(){};
        Equip(float hp,float mp,float def,float value):hp(hp),mp(mp),def(def),value(value){
            name = __func__;
        };
        float hp = 0;
        float mp = 0;
        float def = 0;
        float value = 0;
        operator bool(){
            return value == 0;
        }
        virtual EquipTyp typ(){return tEquip;};
        virtual void equiped(Hero& hero){std::cout<<"equiped"<<std::endl;};
        virtual void takeoff(Hero& hero){};
};
struct hashBaseEquip{
    size_t operator()(const BaseEquip& value) const
    {
        return std::hash<std::string>{}(value.name);
    }
};  

class Medicine: public BaseEquip
{
    public:
        Medicine(){
            name = __func__;
        };

        float hp;
        float mp;
        float atk;
        float def;
        void used(Hero& hero,int n);
        void display(){};
};

const std::vector<Equip> equipstore; 
const std::vector<Medicine> medicinestore;

class Bag;
class Store{
    public:
        void initializeCommodities();
        void refresh();
        void display() const;
        void sold(Equip& equip, int n,Bag& bag);
        void sold(Medicine& medicine, int n,Bag& bag);
        void buy(Equip& equip, int n,Bag& bag);
        void buy(Medicine& medicine, int n,Bag& bag);
    private:
        std::unordered_map<Equip,int, hashBaseEquip> equipcommodities;
        std::unordered_map<Medicine,int,hashBaseEquip> medicinecommodities;
};


class Bag{
    public:
        Bag(){

        }
        friend class Hero;
        friend class Store;
        friend class Equip;
        void get(Equip& equip, int n);
        void get(Medicine& Medicine, int n);
        void display() const;
        void use(Medicine& medicine,int n,Hero& hero);
        void changeequip(Equip& equip,Hero& hero);
        private:
            std::unordered_map<Equip,int,hashBaseEquip> bag;
            std::unordered_map<Medicine,int,hashBaseEquip> medicinebag;
            std::array<Equip, EquipTypCount> equipbag;
            //Equip  equipbag[EquipTypCount] ;
};




class Sword : public Equip
{
    public:
        friend class Bag;
        friend class Hero;
        Sword(float hp,float mp,float def,float value,float atk):
            Equip(hp,mp,def,value),atk(atk){};
        float atk;
        EquipTyp typ(){return tSword;}
        void equiped(Hero& hero);
        void takeoff(Hero& hero);
};

class Stonesword : public Sword
{
    public:
        friend class Bag;
        Stonesword(float hp,float mp,float def,float value,float atk): Sword(hp,mp,def,value,atk){
            name = __func__;
        };
};

class Bronzesword : public Sword
{
    public:
        friend class Bag;
        Bronzesword(float hp,float mp,float def,float value,float atk): Sword(hp,mp,def,value,atk){
            name = __func__;
        };
};

class Ironsword : public Sword
{
    public:
        friend class Bag;
        Ironsword(float hp,float mp,float def,float value,float atk): Sword(hp,mp,def,value,atk){
            name = __func__;
        };
};

class Armhour :public Equip
{
    public:
        friend class Bag;
        Armhour(int hp,int mp,int def,float value):Equip(hp,mp,def,value){
            name = __func__;
        };
        EquipTyp typ(){return tArmhour;}
        void equiped(Hero& hero);
        void takeoff(Hero& hero);
};



class Shoes :public Equip
{
    public:
        friend class Bag;
        Shoes(int hp,int mp,int def,float value):Equip(hp,mp,def,value){
            name = __func__;
        };
        EquipTyp typ(){return tShoes;}
        void equiped(Hero& hero);
        void takeoff(Hero& hero);
};


class RedMedicine : public Medicine
{
    public:
        RedMedicine(){
            name = __func__;
            hp=10;
            mp=0;
        }
        void display()
        {
            std::cout << "hp回复" << std::endl;
        }

     
};

class BlueMedicine : public Medicine
{
    public:
        friend class Hero;
        BlueMedicine(){
            name = __func__;
            hp=0;
            mp=10;
        }
        void display()
        {
            std::cout << "mp回复" << std::endl;
        }
     
};  