
#include "../../include/equip.h"



void Bag::display() const
{
    std::cout << "装备背包:" << std::endl;
    for(const auto& i: equipBag){
        if(i.second >= 0){
            std::cout << i.first->name << i.second << std::endl;
        }
    }

    std::cout << "药水背包:" << std::endl;
    for(const auto& i: medicineBag){
        if(i.second>=0){
            std::cout << i.first->name << i.second << std::endl;
        }
    }

    std::cout << "装备栏:" << std::endl;
    for(const auto& i: equipColumn){
        if(i != nullptr){
            std::cout << i->name << std::endl;
        } else {
            std::cout << "(none)" << std::endl;
        }
    }
}

void Bag::get(std::shared_ptr<Equip> equip, int n){
    equipBag[equip] += n;
}

void Bag::get(std::shared_ptr<Medicine> medicine, int n){
    medicineBag[medicine] += n;
}

void Bag::use(std::shared_ptr<Medicine> medicine, int n, Hero& hero){
    if(hero.hp < hero.hpMax){
        medicineBag[medicine] = medicineBag[medicine] - n;
        medicine->used(hero, n);
    }
    else{
        std::cout << hero.name <<"已经满血" << std::endl;
    }

}

void Bag::changeequip(std::shared_ptr<Equip> equip, Hero& hero) 
{
    /*
    for(const auto& i:equipbag)
    {
        if(i == equip)
        {
            i->takeoff(hero);
            equip->equiped(hero);
            bag[i]++;
            bag[equip]--;
        }
    }
    //const auto tup = std::make_pair(equip.number, equip);
    equipbag[equip->typ()] = equip;
    */
    
    if(equipColumn[equip->typ()] == nullptr) {
        equip->equiped(hero);
        equipColumn[equip->typ()] = equip;
    }
    else
    {
        std::shared_ptr<Equip> old = equipColumn[equip->typ()];
        if(equipColumn[equip->typ()]) {
            old->takeoff(hero);
        }
        equipBag[old]++;
        equipBag[equip]--;
        equipColumn[equip->typ()] = equip;
    //  equipbag[equip.typ()].equiped(hero);
        equip->equiped(hero);
    }
}

bool BaseEquip::operator== (const BaseEquip& other) const{
    return name == other.name;
}

#define WithName(cls) cls::cls(){name = __func__;}

WithName(Equip)

Equip::Equip(double hp, double mp, double def, double value):hp(hp), mp(mp), def(def), value(value){
    name = __func__;
};

Equip::operator bool(){
    return value != 0;
}

#define __unImplement {std::cerr << __func__ << " unimplemented" << std::endl; abort();}

EquipTyp
Equip::typ()__unImplement


void Equip::equiped(Hero& hero) __unImplement
void Equip::takeoff(Hero& hero) __unImplement


size_t hashBaseEquip::operator() (const std::shared_ptr<BaseEquip> value) const{
    return std::hash<std::string>{}(value->name);
}


WithName(Medicine)


void Medicine::display() __unImplement


Store::Store(
            std::vector<std::shared_ptr<Equip>> equipstore/*={}*/,//商店初始装备
            std::vector<std::shared_ptr<Medicine>> medicinestore/*={}*/
        )
{
    for (const auto& i : equipstore){
        equipCommodities.insert(std::make_pair(i, 1));   
    }
    for (const auto& i : medicinestore){
        medicineCommodities.insert(std::make_pair(i, 999));   
    }
}


void Store::display() const {
    std::cout << "装备:" << std::endl;
    for(const auto& i: equipCommodities){
        std::cout << i.first->name << i.second << std::endl;
    }
    std::cout << "药水:" << std::endl;
    for(const auto& i: medicineCommodities){
        std::cout << i.first->name << i.second << std::endl;
    }

}

void Store::sold(std::shared_ptr<Equip> equip, int n, Bag& bag, Hero& hero){
    if(equipCommodities[equip] >= n){
        equipCommodities[equip] = equipCommodities[equip] - n;
        bag.get(equip, n);
        hero.adjustGold(-(n * equip->value));
    }
    else{
        std::cout << "超出数量" << std::endl;
     }
}

void Store::sold(std::shared_ptr<Medicine> medicine, int n, Bag& bag, Hero& hero){
    if(medicineCommodities[medicine] >= n){
        medicineCommodities[medicine] = medicineCommodities[medicine] - n;
        bag.get(medicine, n);
        hero.adjustGold(-(n * medicine->value));
    }
    else{
        std::cout << "超出数量" << std::endl;
     }
}

void Store::buy(std::shared_ptr<Equip> equip, int n, Bag& bag, Hero& hero){
    if(bag.equipBag[equip] >= n){
        bag.equipBag[equip] -= n;
        hero.adjustGold(n * equip->value);
    }
    else{
        std::cout << "超出数量" << std::endl;
    }
}
void Store::buy(std::shared_ptr<Medicine> medicine, int n, Bag& bag, Hero& hero){
    if(bag.medicineBag[medicine] >= n){
        bag.medicineBag[medicine] -= n;
        hero.adjustGold(n * medicine->value);
    }
    else{
        std::cout << "超出数量" << std::endl;
    }
}


Sword::Sword(double hp, double mp, double def, double value, double atk):
    Equip(hp, mp, def, value), atk(atk){};

#define RetType(cls) EquipTyp cls::typ(){return t##cls;}

RetType(Sword)


void Sword::equiped(Hero& hero){
    hero.hpMax += hp;
    hero.mpMax += mp;
    hero.defend += def;
    hero.attack += atk;
}

void Sword::takeoff(Hero& hero){
    hero.hpMax -= hp;
    hero.mpMax -= mp;
    hero.defend -= def;
    hero.attack -= atk;
}


#define ImplSword(cls) \
cls::cls(double hp, double mp, double def, double value, double atk): Sword(hp, mp, def, value, atk){\
    name = __func__;\
}\

ImplSword(StoneSword)
ImplSword(BronzeSword)
ImplSword(IronSword)


RetType(Armhour)

#define ArmOrShoe(cls) \
cls::cls(int hp, int mp, int def, double value):Equip(hp, mp, def, value){\
    name = __func__;\
}

ArmOrShoe(Armhour)
ArmOrShoe(Shoes)



void Armhour::equiped(Hero& hero){
    hero.hpMax += hp;
    hero.mpMax += mp;
    hero.defend += def;
}

void Armhour::takeoff(Hero& hero){
    hero.hpMax -= hp;
    hero.mpMax -= mp;
    hero.defend -= def;
}


RetType(Shoes)

void Shoes::equiped(Hero& hero){
    hero.hpMax += hp;
    hero.mpMax += mp;
    hero.defend += def;
}

void Shoes::takeoff(Hero& hero){
    hero.hpMax -= hp;
    hero.mpMax -= mp;
    hero.defend -= def;
}

void Medicine::used(Hero& hero, int n){
    if(hero.hp + n * hp <= hero.hpMax){
        hero.hp += n * hp;
    }else{
        hero.hp = hero.hpMax;
    }

    if(hero.mp + n * mp <= hero.mpMax){
        hero.mp += n * mp;
    }else{
        hero.mp = hero.mpMax;
    }
    hero.attack += atk * n;
    hero.defend += def * n;
}
RedMedicine::RedMedicine(){
    name = __func__;
    hp = 10;
    mp = 0;
    value = 10;
}

void RedMedicine::display() const{
    std::cout << "hp回复" << std::endl;
}

BlueMedicine::BlueMedicine(){
    name = __func__;
    hp = 0;
    mp = 10;
    value = 10;
}

void BlueMedicine::display() const{
    std::cout << "mp回复" << std::endl;
}
