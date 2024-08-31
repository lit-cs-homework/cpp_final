
#include "../../include/equip.h"


using PBEquip = std::shared_ptr<BaseEquip>;


std::unordered_map<
    std::string,
    std::function<void(PBEquip)>
> bagmap;


#define show(cls,str,suffix)\
{\
    std::cout << #str << ":" << std::endl;\
    for(const auto& i: cls##suffix){\
        if(i.second >= 0){\
            std::cout << i.first->name << " " << i.second << std::endl;\
        }\
    }\
    std::cout << std::endl;\
}\


void Bag::display() const
{
    // std::cout << "装备背包:" << std::endl;
    // for(const auto& i: equipBag){
    //     if(i.second >= 0){
    //         std::cout << i.first->name << " " << i.second << std::endl;
    //     }
    // }
    show(equip,装备背包,Bag);

    // std::cout << "药水背包:" << std::endl;
    // for(const auto& i: medicineBag){
    //     if(i.second>=0){
    //         std::cout << i.first->name << " " << i.second << std::endl;
    //     }
    // }
    show(medicine,药水背包,Bag);

    std::cout << "装备栏:" << std::endl;
    for(const auto& i: equipColumn){
        if(i != nullptr){
            std::cout << i->name << std::endl;
        } else {
            std::cout << "(none)" << std::endl;
        }
    }
}

// #define void Bag::get(std::shared_ptr<typ>,cls,int n)\
// {\
//     cls##Bag[cls] += n;\
// }\

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
        std::cout << hero.name <<" 已经满血" << std::endl;
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

#define withName(cls) \
    name = __func__;\
    bagmap[name] = [](PBEquip p){ p = std::make_shared<cls>(); };\

#define DeclWithName(cls) cls::cls(){ withName(cls);}


Equip::Equip(){name = __func__;}
Equip::Equip(double hp, double mp, double def, double value):hp(hp), mp(mp), def(def), value(value){
    name = __func__;
};

void Equip::setValue(double value){
    this->value = value;
}

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


DeclWithName(Medicine)


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
    // showEquipCommodities();
    show(equip,装备,Commodities);
    show(medicine,药水,Commodities);
}

// void Store::showEquipCommodities() const
// {
//     std::cout << "装备:" << std::endl;
//     for(const auto& i: equipCommodities){
//         std::cout << i.first->name << " " << i.second << std::endl;
//     }
//     std::cout << std::endl;
// }

// void Store::showMedicineCommodities() const
// {
//     std::cout << "药水:" << std::endl;
//     for(const auto& i: medicineCommodities){
//         std::cout << i.first->name << " " << i.second << std::endl;
//     }
//     std::cout << std::endl
// }


#define fun(typ,cls,suffix1,suffix2,action,...)\
{\
    std::vector<std::shared_ptr<typ>> cls##suffix1;\
    cls##suffix1.reserve(__VA_ARGS__ __VA_OPT__(.) cls##suffix2.size());\
    for(auto& i: __VA_ARGS__ __VA_OPT__(.) cls##suffix2) {\
        cls##suffix1.push_back(i.first);\
    }\
    for(size_t i = 0; i < cls##suffix1.size(); i++){\
        const auto& ele = cls##suffix1[i];\
        styledWrite(styleBright, (std::to_string(i+1)+'.').c_str());\
        styledWrite(styleItalic, ele->name.c_str());\
        std::cout << "  ";\
        styledWriteLine(styleItalic, (std::to_string(__VA_ARGS__ __VA_OPT__(.) cls##suffix2[ele]).c_str()));\
    }\
    std::cout << "请输入要购买的商品的序号和数量" << std::endl;\
    int i;\
    std::cin >> i;\
    int n;\
    std::cin >> n;\
    action(cls##suffix1[i-1],n,bag,hero);\
}\

// #define fun1(typ,cls)\
// {\
//     std::vector<std::shared_ptr<typ>> cls##bag;\
//     cls##bag.reserve(cls##bag.size());\
//     for(auto& i: bag.cls##Bag) {\
//         cls##bag.push_back(i.first);\
//     }\
//     for(size_t i = 0; i < cls##bag.size(); i++){\
//         const auto& ele = cls##bag[i];\
//         styledWrite(styleBright, (std::to_string(i+1)+'.').c_str());\
//         styledWriteLine(styleItalic, ele->name.c_str());\
//     }\
//     std::cout << "请输入序号和数量" << std::endl;\
//     int i;\
//     std::cin >> i;\
//     int n;\
//     std::cin >> n;\
//     buy(cls##bag[i],n,bag,hero);\
// }


void Store::trade(Bag& bag,Hero& hero){
    char choice;
    while(true)
    {
        display();
        std::cout << "请输入数字" <<std::endl<< "0:退出 " << "1:购买装备 " << "2:购买药水 " << "3:出售装备 " << "4:出售药水" << "5:背包展示" << std::endl;
        std::cin >> choice;
        if(choice == '0')
        {
            break;
        }
        else if (choice == '1')
        {
            //showEquipCommodities();
            fun(Equip,equip,store,Commodities,sold);
        }
        else if(choice == '2')
        {
            fun(Medicine,medicine,store,Commodities,sold);
        }
        else if(choice == '3')
        {
            fun(Equip,equip,bag,Bag,buy,bag);
        }
        else if(choice == '4')
        {
            fun(Medicine,medicine,bag,Bag,buy,bag);
        }
        else if(choice == '5')
        {
            bag.display();
        }
        else
        {
            std::cout << "输入错误,请重新输入" << std::endl;
        }
    }
}

void Store::sold(std::shared_ptr<Equip> equip, int n, Bag& bag, Hero& hero){
    if(equipCommodities[equip] >= n && hero.getGold() >= n * equip->value){
        equipCommodities[equip] = equipCommodities[equip] - n;
        bag.get(equip, n);
        hero.adjustGold(-(n * equip->value));
    }
    else{
        std::cout << "超出数量" << std::endl;
     }
}

void Store::sold(std::shared_ptr<Medicine> medicine, int n, Bag& bag, Hero& hero){
    if(medicineCommodities[medicine] >= n && hero.getGold() >= n * medicine->value){
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


Sword::Sword(double value, double atk): atk(atk){
    setValue(value);
};

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


#define ImplSword(cls, ...) \
cls::cls(): Sword(__VA_ARGS__){\
    withName(cls);\
}\

ImplSword(StoneSword , 10, 5)
ImplSword(BronzeSword, 20, 10)
ImplSword(IronSword  , 30, 15)


RetType(Armhour)

#define def4(cls) \
cls::cls(double value, double hp, double mp, double def): Equip(value, hp, mp, def){withName(cls);}


#define ArmOrShoe(cls, ...) def4(cls);\
cls::cls(): cls(__VA_ARGS__){}

ArmOrShoe(Armhour,10, 10, 10, 10)
ArmOrShoe(Shoes  ,10, 10, 10, 10)

#undef def4
#undef ArmOrShoe

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
    withName(RedMedicine);
    hp = 10;
    mp = 0;
    value = 10;
}

void RedMedicine::display() const{
    std::cout << "hp回复" << std::endl;
}

BlueMedicine::BlueMedicine(){
    withName(BlueMedicine);
    hp = 0;
    mp = 10;
    value = 10;
}

void BlueMedicine::display() const{
    std::cout << "mp回复" << std::endl;
}
