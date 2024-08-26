#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include <string>
#include <utility>
#include <vector>
#include <array>




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
};

enum EquipTyp{
    tEquip,    
    tSword,
    tArmhour,
    tShoes,
};
static constexpr size_t EquipTypCount = 4;


class BaseEquip{
    public:
        std::string name;
        bool operator== (const BaseEquip& other)const;
};


class Equip: public BaseEquip{
    public:
        Equip();
        Equip(double hp,double mp,double def,double value);
        double hp = 0;
        double mp = 0;
        double def = 0;
        double value = 0;
        operator bool();
        virtual EquipTyp typ();
        virtual void equiped(Hero& hero);
        virtual void takeoff(Hero& hero);
};

struct hashBaseEquip{
    size_t operator()(const BaseEquip& value) const;
};  

class Medicine: public BaseEquip
{
    public:
        Medicine();
        double hp;
        double mp;
        double atk;
        double def;
        void used(Hero& hero,int n);
        virtual void display();
};


class Bag;
class Store{
    public:
        Store(std::vector<Equip> equipstore = {},std::vector<Medicine> medicinestore = {});
        //void refresh();
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
        Sword(double hp,double mp,double def,double value,double atk);
        double atk;
        EquipTyp typ();
        void equiped(Hero& hero);
        void takeoff(Hero& hero);
};

class Stonesword : public Sword
{
    public:
        friend class Bag;
        Stonesword(double hp,double mp,double def,double value,double atk);
};

class Bronzesword : public Sword
{
    public:
        friend class Bag;
        Bronzesword(double hp,double mp,double def,double value,double atk);
};

class Ironsword : public Sword
{
    public:
        friend class Bag;
        Ironsword(double hp,double mp,double def,double value,double atk);
};

class Armhour :public Equip
{
    public:
        friend class Bag;
        Armhour(int hp,int mp,int def,double value);
        EquipTyp typ();
        void equiped(Hero& hero);
        void takeoff(Hero& hero);
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
        void display();
};

class BlueMedicine : public Medicine
{
    public:
        friend class Hero;
        BlueMedicine();
        void display();
};  