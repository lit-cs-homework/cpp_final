
#include "../../include/equip.h"



void Bag::display() const
{
    for(const auto& i: bag){
        if(i.second>=0){
            std::cout <<i.first.name << i.second <<std::endl;
        }
    } 
}

void Bag::get(Equip& equip, int n){
    bag[equip] = bag[equip] + n;
}

void Bag::get(Medicine& medicine, int n)
{
    medicinebag[medicine] += n;
}

void Bag::use(Medicine& medicine, int n,Hero& hero){
    medicinebag[medicine] = medicinebag[medicine] - n;
    medicine.used(hero,n);
}

void Bag::changeequip(Equip& equip,Hero& hero)
{
    /*
    for(const auto& i:equipbag)
    {
        if(i.second == equip)
        {
            i.second.takeoff(hero);
            equip.equiped(hero);
            bag[i.second]++;
            bag[equip]--;
        }
    }
    //const auto tup = std::make_pair(equip.number,equip);
    equipbag[equip] = equip;
    */
   auto& old = equipbag[equip.typ()];
   if(old) {
     old.takeoff(hero);
   }
   equipbag[equip.typ()] = equip;
   equipbag[equip.typ()].equiped(hero);
}

bool BaseEquip::operator== (const BaseEquip& other)const
{
    return name==other.name;
}

Equip::Equip(){}

Equip::Equip(double hp,double mp,double def,double value):hp(hp),mp(mp),def(def),value(value){
    name = __func__;
};

Equip::operator bool(){
    return value == 0;
}

#define __unImplement {std::cerr<<__func__ <<" unimplemented"<<std::endl; abort();}

EquipTyp
Equip::typ()__unImplement


void Equip::equiped(Hero& hero) __unImplement
void Equip::takeoff(Hero& hero) __unImplement


size_t hashBaseEquip::operator()(const BaseEquip& value) const
    {
        return std::hash<std::string>{}(value.name);
    }

#define WithName(cls) cls::cls(){name==__func__;}

WithName(Medicine)


void Medicine::display() __unImplement


Store::Store(
            std::vector<Equip> equipstore/*={}*/,//商店初始装备
            std::vector<Medicine> medicinestore/*={}*/
        )
{
    for (const auto& i : equipstore)
    {
        equipcommodities.insert(std::make_pair(i, 1));   
    }
    for (const auto& i : medicinestore)
    {
        medicinecommodities.insert(std::make_pair(i, 999));   
    }
}


void Store::display() const{
    for(const auto& i: equipcommodities){
        std::cout <<i.first.name << i.second <<std::endl;
    }
    for(const auto& i: medicinecommodities){
        std::cout <<i.first.name << i.second <<std::endl;
    }

}

void Store::sold(Equip& equip, int n,Bag& bag){
    if(equipcommodities[equip]>=n){
        equipcommodities[equip] = equipcommodities[equip] - n;
        bag.get(equip,n);
    }
    else{
        std::cout << "超出数量" << std::endl;
     }
}

void Store::sold(Medicine& medicine, int n,Bag& bag){
    if(medicinecommodities[medicine]>=n){
        medicinecommodities[medicine] = medicinecommodities[medicine] - n;
        bag.get(medicine,n);
    }
    else{
        std::cout << "超出数量" << std::endl;
     }
}

void Store::buy(Equip& equip, int n,Bag& bag)
{
    if(bag.bag[equip]>=n)
    {
        bag.bag[equip]+=n;
    }
}
void Store::buy(Medicine& medicine, int n,Bag& bag)
{
    if(bag.medicinebag[medicine]>=n)
    {
        bag.medicinebag[medicine]+=n;
    }
}


Sword::Sword(double hp,double mp,double def,double value,double atk):
    Equip(hp,mp,def,value),atk(atk){};

#define RetType(cls) EquipTyp cls::typ(){return t##cls;}

RetType(Sword)


void Sword::equiped(Hero& hero)
{
    hero.hpMax += hp;
    hero.mpMax += mp;
    hero.defend += def;
    hero.attack += atk;
}
void Sword::takeoff(Hero& hero)
{
    hero.hpMax -= hp;
    hero.mpMax -= mp;
    hero.defend -= def;
    hero.attack -= atk;
}


#define ImplSword(cls) \
cls::cls(double hp,double mp,double def,double value,double atk): Sword(hp,mp,def,value,atk){\
    name = __func__;\
}\

ImplSword(Stonesword)
ImplSword(Bronzesword)
ImplSword(Ironsword)


RetType(Armhour)

#define ArmOrShoe(cls) \
cls::cls(int hp,int mp,int def,double value):Equip(hp,mp,def,value){\
    name = __func__;\
}

ArmOrShoe(Armhour)
ArmOrShoe(Shoes)



void Armhour::equiped(Hero& hero)
{
    hero.hpMax += hp;
    hero.mpMax += mp;
    hero.defend += def;
}
void Armhour::takeoff(Hero& hero)
{
    hero.hpMax -= hp;
    hero.mpMax -= mp;
    hero.defend -= def;
}


RetType(Shoes)

void Shoes::equiped(Hero& hero)
{
    hero.hpMax += hp;
    hero.mpMax += mp;
    hero.defend += def;
}
void Shoes::takeoff(Hero& hero)
{
    hero.hpMax -= hp;
    hero.mpMax -= mp;
    hero.defend -= def;
}

void Medicine::used(Hero& hero,int n)
{
    if(hero.hp+hp<=hero.hpMax)
    {
        hero.hp += hp*n;
    }
    if(hero.mp+mp<=hero.mpMax)
    {
        hero.mp += mp*n;
    }
    hero.attack += atk*n;
    hero.defend += def*n;
}
RedMedicine::RedMedicine(){
    name = __func__;
    hp=10;
    mp=0;
}

void RedMedicine::display()
{
    std::cout << "hp回复" << std::endl;
}

BlueMedicine::BlueMedicine(){
    name = __func__;
    hp=0;
    mp=10;
}

void BlueMedicine::display()
{
    std::cout << "mp回复" << std::endl;
}
