
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

void Store::initializeCommodities()
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
void Store::refresh()
{
    initializeCommodities();
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