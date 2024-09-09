
#include "../../include/equip.h"
#include "../../include/utils.h"
#include <cstdio>

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border
#include "ftxui/dom/node.hpp"
#include "ftxui/dom/elements.hpp"  // for color, Fit, LIGHT, align_right, bold, DOUBLE
#include "ftxui/dom/table.hpp"      // for Table, TableSelection
#include "ftxui/screen/screen.hpp"

using namespace ftxui;

std::unordered_map<
    std::string,
    std::function<void(std::shared_ptr<Equip>&)>
> equipbagmap;

std::unordered_map<
    std::string,
    std::function<void(std::shared_ptr<Medicine>&)>
> medicinebagmap;

std::unordered_map<
    std::string,
    std::function<void(std::shared_ptr<Equip>&)>
> equipcolumnmap;








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

void Bag::displayEquipColumnCil(Hero& hero)
{
    while(true)
    {
        std::cout << "装备栏:" << std::endl;
        int p = 0;
        for(const auto& i: equipColumn){
            if(i != nullptr){
                p++;
                std::cout << i->typ() << "." << i->name << std::endl;
            } else {
                p++;
                if(p != 1)
                {
                    std::cout << "(none)" << std::endl;
                }
            }
        }
        std::cout << "是否要更换装备,请输入y或者n,输入n退出" << std::endl;
        char choice;
        std::cin >> choice;
        if(choice == 'y')
        {
            std::cout << "装备背包:" << std::endl;
            int k = 0;
            int j = 0;
            for(const auto& i: equipBag){
                if(i.second >= 0){
                    std::cout << ++j << ". ";
                    std::cout << i.first->name << " " << i.second << std::endl;
                }
            }
            int key;
            std::cout << "请输入序号" << std::endl;
            std::cin >> key;
            if(key > j)
            {
                std::cout << "请重新输入" << std::endl;
            }
            for(const auto& i: equipBag){
                k++;
                if(k==key)
                {
                    changeequip(i.first,hero);
                }
            }
            
        }
        else if(choice == 'n')
        {
            break;
        }
        else
        {
            std::cout <<  "请重新输入" << std::endl;
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

bool Bag::use(std::shared_ptr<Medicine> medicine, int n, Hero& hero){
    if(hero.hp < hero.hpMax && medicineBag[medicine] >= n){
        medicineBag[medicine] = medicineBag[medicine] - n;
        medicine->used(hero, n);
        return true;
    }
    else{
        return false;
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
        equipBag[equip]--;
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

#define withName1(cls)\
    name = __func__;\
    const char* const MapName##cls = __func__;\
    equipbagmap[name] = [](std::shared_ptr<Equip>& p){ p = std::make_shared<cls>(); };\
    equipcolumnmap[name] = [](std::shared_ptr<Equip>& p){ p = std::make_shared<cls>(); };\

#define withName2(cls) \
    name = __func__;\
    medicinebagmap[name] = [](std::shared_ptr<Medicine>& p){ p = std::make_shared<cls>(); };\

#define DeclWithName2(cls) cls::cls(){ withName2(cls);}



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


DeclWithName2(Medicine)


std::string Medicine::display()
{
    return "回复hp "+std::to_string(hp) + " 回复mp"+std::to_string(mp);
}


Store::Store(
            std::vector<std::shared_ptr<Equip>> equipstore/*={}*/,//商店初始装备
            std::vector<std::shared_ptr<Medicine>> medicinestore/*={}*/
        )
{
    for (const auto& i : equipstore){
        equipCommodities[i] = 1;   
    }
    for (const auto& i : medicinestore){
        medicineCommodities[i] = 999;   
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


#define fun(typ,cls,str,suffix1,suffix2,action,...)\
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
    std::cout << #str << std::endl;\
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

Store::Store(){};
void Store::refresh(){
    std::shared_ptr<WoodenSword> l = std::make_shared<WoodenSword>  ();
    std::shared_ptr<ClothArmhour> m = std::make_shared<ClothArmhour>  ();
    std::shared_ptr<HeavenlyDemonArmhour> n = std::make_shared<HeavenlyDemonArmhour>  ();
    std::shared_ptr<HeavenlySword> o = std::make_shared<HeavenlySword>  ();
    std::shared_ptr<ShadowShoes> p = std::make_shared<ShadowShoes> ();

    std::shared_ptr<GreenSword> a = std::make_shared<GreenSword>  ();
    std::shared_ptr<IronSword> b = std::make_shared<IronSword>    ();
    std::shared_ptr<CrystalIceArmhour> c = std::make_shared<CrystalIceArmhour> ();
    std::shared_ptr<BlazeArmhour> d = std::make_shared<BlazeArmhour> ();
    std::shared_ptr<SwiftShoes> e = std::make_shared<SwiftShoes>  ();
    std::shared_ptr<ThunderLightingShoes> f = std::make_shared<ThunderLightingShoes>  ();    
    std::shared_ptr<LifeMedicine> g = std::make_shared<LifeMedicine>() ;
    std::shared_ptr<LifeResortingMedicine> h = std::make_shared<LifeResortingMedicine>() ;
    std::shared_ptr<SoulRevivingMedicine> i = std::make_shared<SoulRevivingMedicine>() ;
    std::shared_ptr<SpiritConcentratingMedicine> j = std::make_shared<SpiritConcentratingMedicine>() ;
    std::shared_ptr<HeavenlyOriginMedicine> k = std::make_shared<HeavenlyOriginMedicine>() ;


    
    std::vector<std::shared_ptr<Equip>> equipstore = {a,b,c,d,e,f};
    std::vector<std::shared_ptr<Medicine>> medicinestore = {g,h,i,j,k};

    for (const auto& i : equipstore){
        equipCommodities[i] = 1;   
    }
    for (const auto& i : medicinestore){
        medicineCommodities[i] = 999;   
    }
}

void Store::tradeCli(Bag& bag,Hero& hero){
    char choice;
    while(true)
    {
        display();
        std::cout << "请输入数字" <<std::endl<< "0:退出 " << "1:购买装备 " << "2:购买药水 " << "3:出售装备 " << "4:出售药水 " << "5:花钱刷新商店 " << "6:背包展示" << std::endl;
        std::cin >> choice;
        if(choice == '0')
        {
            break;
        }
        else if (choice == '1')
        {
            //showEquipCommodities();
            fun(Equip,equip,请输入要购买的商品的序号和数量,store,Commodities,sold);
        }
        else if(choice == '2')
        {
            fun(Medicine,medicine,请输入要购买的商品的序号和数量,store,Commodities,sold);
        }
        else if(choice == '3')
        {
            fun(Equip,equip,请输入要出售的商品的序号和数量,bag,Bag,buy,bag);
        }
        else if(choice == '4')
        {
            fun(Medicine,medicine,请输入要出售的商品的序号和数量,bag,Bag,buy,bag);
        }
        else if(choice == '5')
        {
            const int refreshgold = 5;
            if(hero.getGold() < refreshgold ){
                std::cout << "金钱不够,刷新失败"<< std::endl;
            }
            else{
                hero.adjustGold(-refreshgold);
            }
        }
        else if(choice == '6')
        {
            bag.display();
        }
        else
        {
            std::cout << "输入错误,请重新输入" << std::endl;
        }
    }
}

bool Store::sold(std::shared_ptr<Equip> equip, int n, Bag& bag, Hero& hero){
    if(equipCommodities[equip] >= n && hero.getGold() >= n * equip->value){
        equipCommodities[equip] = equipCommodities[equip] - n;
        bag.get(equip, n);
        hero.adjustGold(-(n * equip->value));
        return true;
    }
    else{
        return false;
     }
}

bool Store::sold(std::shared_ptr<Medicine> medicine, int n, Bag& bag, Hero& hero){
    if(medicineCommodities[medicine] >= n && hero.getGold() >= n * medicine->value){
        medicineCommodities[medicine] -=  n;
        bag.get(medicine, n);
        hero.adjustGold(-(n * medicine->value));
        return true;
    }
    else{
        return false;
     }
}

bool Store::buy(std::shared_ptr<Equip> equip, int n, Bag& bag, Hero& hero){
    if(bag.equipBag[equip] >= n){
        bag.equipBag[equip] -= n;
        hero.adjustGold(n * equip->value);
        return true;
    }
    else{
        return false;
    }
}
bool Store::buy(std::shared_ptr<Medicine> medicine, int n, Bag& bag, Hero& hero){
    if(bag.medicineBag[medicine] >= n){
        bag.medicineBag[medicine] -= n;
        hero.adjustGold(n * medicine->value);
        return true;
    }
    else{
        return false;
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


std::string Sword::display1() const
{
    return "攻击力 "+std::to_string(atk);
}

// std::string WoodenSword::display() const
// {
//     return "攻击力 "+std::to_string(atk);
// }

// std::string StoneSword::display() const
// {
//     return "攻击力 "+std::to_string(atk);
// }

// std::string BronzeSword::display() const
// {
//     return "攻击力 "+std::to_string(atk);
// }

// std::string IronSword::display() const
// {
//     return "攻击力 "+std::to_string(atk);
// }

// std::string GreenSword::display() const
// {
//     return "攻击力 "+std::to_string(atk);
// }

// std::string HeavenlySword::display() const
// {
//     return "攻击力 "+std::to_string(atk);
// }



#define ImplClsWithBase(cls,base,...) \
cls::cls(): base(__VA_ARGS__){\
    withName1(cls);\
}

#define ImplSword(cls,...) ImplClsWithBase(cls, Sword, __VA_ARGS__)

ImplSword(WoodenSword, 10, 10)
ImplSword(IronSword  , 100, 100)
ImplSword(GreenSword , 400, 400)
ImplSword(HeavenlySword,6000,6000)


ImplSword(StoneSword , 10, 5)
ImplSword(BronzeSword, 20, 10)


RetType(Armhour)

#define def4(cls) \
cls::cls(double value, double hp, double mp, double def): Equip(value, hp, mp, def){withName1(cls);}


#define ArmOrShoe(cls,...) def4(cls);\
cls::cls(): cls(__VA_ARGS__){}

ArmOrShoe(Armhour,10, 10, 10, 10)
ArmOrShoe(Shoes  ,10, 10, 10, 10)



#define ImplArm(cls,...) ImplClsWithBase(cls, Armhour, __VA_ARGS__)

ImplArm(ClothArmhour,10, 30, 0, 10)
ImplArm(CrystalIceArmhour,100,200,200,60)
ImplArm(BlazeArmhour,400,600,400,100)
ImplArm(HeavenlyDemonArmhour,6000,6000,3000,1500)

#undef ImplArm

#define ImplShoe(cls,...) ImplClsWithBase(cls, Shoes, __VA_ARGS__)


ImplShoe(SwiftShoes,100,300,50,20)
ImplShoe(ThunderLightingShoes,400,600,100,30)
ImplShoe(ShadowShoes,2000,2000,1000,500)


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

std::string Armhour::display1() const
{
    return "hp "+std::to_string(hp)+" mp "+std::to_string(mp)+" 防御 "+std::to_string(def);
}

// std::string ClothArmhour::display() const
// {
//     return "hp "+std::to_string(hp)+" mp "+std::to_string(mp)+" 防御 "+std::to_string(def);
// }

// std::string CrystalIceArmhour::display() const
// {
//     return "hp "+std::to_string(hp)+" mp "+std::to_string(mp)+" 防御 "+std::to_string(def);
// }

// std::string BlazeArmhour::display() const
// {
//     return "hp "+std::to_string(hp)+" mp "+std::to_string(mp)+" 防御 "+std::to_string(def);
// }

// std::string HeavenlyDemonArmhour::display() const
// {
//     return "hp "+std::to_string(hp)+" mp "+std::to_string(mp)+" 防御 "+std::to_string(def);
// }


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

std::string Shoes::display1() const
{
    return "hp "+std::to_string(hp)+" mp "+std::to_string(mp)+" 防御 "+std::to_string(def);
}

// std::string SwiftShoes::display() const
// {
//     return "hp "+std::to_string(hp)+" mp "+std::to_string(mp)+" 防御 "+std::to_string(def);
// }

// std::string ThunderLightingShoes::display() const
// {
//     return "hp "+std::to_string(hp)+" mp "+std::to_string(mp)+" 防御 "+std::to_string(def);
// }

// std::string ShadowShoes::display() const
// {
//     return "hp "+std::to_string(hp)+" mp "+std::to_string(mp)+" 防御 "+std::to_string(def);
// }

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
}
RedMedicine::RedMedicine(){
    withName2(RedMedicine);
    hp = 10;
    mp = 0;
    value = 10;
}

std::string RedMedicine::display() const{
    return "回复hp"+std::to_string(hp);
}

LifeMedicine::LifeMedicine(){
    withName2(LifeMedicine);
    hp = 50;
    mp = 0;
    value = 20;
}

std::string LifeMedicine::display() const{
    return "回复hp"+std::to_string(hp);
}

LifeResortingMedicine::LifeResortingMedicine(){
    withName2(LifeResortingMedicine);
    hp = 200;
    mp = 0;
    value = 50;
}

std::string LifeResortingMedicine::display() const{
    return "回复hp"+std::to_string(hp);
}

SoulRevivingMedicine::SoulRevivingMedicine(){
    withName2(SoulRevivingMedicine);
    hp = 300;
    mp = 0;
    value = 75;
}

std::string SoulRevivingMedicine::display() const{
    return "回复hp"+std::to_string(hp);
}

BlueMedicine::BlueMedicine(){
    withName2(BlueMedicine);
    hp = 0;
    mp = 10;
    value = 10;
}

std::string BlueMedicine::display() const{
    return "回复mp"+std::to_string(mp);
}

SpiritConcentratingMedicine::SpiritConcentratingMedicine(){
    withName2(SpiritConcentratingMedicine);
    hp = 0;
    mp = 30;
    value = 20;
}

std::string SpiritConcentratingMedicine::display() const{
    return "回复mp"+std::to_string(mp);
}

HeavenlyOriginMedicine::HeavenlyOriginMedicine(){
    withName2(HeavenlyOriginMedicine);
    hp = 0;
    mp = 100;
    value = 60;
}

std::string HeavenlyOriginMedicine::display() const{
    return "回复mp"+std::to_string(mp);
}

HolyMedicine::HolyMedicine(){
    withName2(HolyMedicine);
    hp = 10000;
    mp = 5000;
    value = 999;
}

std::string HolyMedicine::display() const{
    return "回复hp "+std::to_string(hp) + " 回复mp"+std::to_string(mp);
}

static
ButtonOption Style(){
    auto option = ButtonOption::Animated();
    option.transform = [](const EntryState& s) {
    auto element = text(s.label);
    if (s.focused) {
      element |= bold;
    }
    return element | center | borderEmpty | flex;
  };
  return option;
}



bool hasEnding(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

static
ftxui::Table createBagTable(const Hero& hero,const Bag& bag)
{
    std::vector<std::vector<std::string>> vec;
    vec.push_back(
        {"玩家背包"}
    );
    vec.push_back(
        {"序号", "名称", "数量"}
    );
    auto i = 1;
    #define add(p) do{\
        if (p.second != 0) \
            vec.push_back({std::to_string(i), p.first->name, std::to_string(p.second)}); i++;}while(0)
    for(const auto& p: bag.equipBag) add(p);
    for(const auto& p: bag.medicineBag) add(p);
    return Table(vec);
}

static
ftxui::Table createEquipColumnTable(Hero& hero,const Bag& bag)
{
    std::vector<std::vector<std::string>> vec;
    vec.push_back({"装备栏"});
    vec.push_back(
        {"背包金币数量:", std::to_string(hero.getGold())}
    );
    vec.push_back(
        {"类型","剑", "盔甲","鞋子"}
    );
    auto i = 1;
    std::string str1;
    std::string str2;
    std::string str3;
    if(bag.equipColumn[1] == nullptr ) str1 = "None";else str1=bag.equipColumn[1]->name;
    if(bag.equipColumn[2] == nullptr ) str2 = "None";else str2=bag.equipColumn[2]->name;
    if(bag.equipColumn[3] == nullptr ) str3 = "None";else str3=bag.equipColumn[3]->name;
    vec.push_back({"名称",str1,str2,str3});
    return Table(vec);
}

// digits(float) is 15, a.k.a.
// Number of decimal digits that can be represented in a 64-bit floating-point type without losing precision
// is 15,
// so 15+1(dot)+1(NUL char)  ->  17 is enough
// And x won't be negative, so no sign char will be preappended.
static char buffer[17];

static std::string formatCurrency(double x) {
    sprintf(buffer, "%.2f", x);
    return std::string(buffer);
}

static
ftxui::Table createPriceTable(const Store& store)
{
    std::vector<std::vector<std::string>> vec;
    vec.push_back(
        {"价格表"}
    );
    vec.push_back(
        {"序号", "名称", "价格","数量"}
    );
    auto i = 1;
    #define add1(p) do{\
        if(p.second!=0) vec.push_back({\
        std::to_string(i), p.first->name, formatCurrency(p.first->value),std::to_string(p.second)\
        }); i++;}while(0)
    for(const auto& p: store.equipCommodities) add1(p);
    for(const auto& p: store.medicineCommodities) add1(p);
    return Table(vec);
}


static
ftxui::Element getBagTableElement(const Hero& hero,const Bag& bag)
{
  auto table = createBagTable(hero, bag);
  table.SelectAll().Border(LIGHT);
  table.SelectColumn(0).Border(LIGHT);
  table.SelectColumn(2).Border(LIGHT);
  table.SelectRow(0).Decorate(bold);
  table.SelectRow(0).SeparatorVertical(LIGHT);
  table.SelectRow(0).Border(DOUBLE);
  table.SelectRow(0).Border(DOUBLE);
  return table.Render();
}

static
ftxui::Element getEquipColumnTableElement(Hero& hero,const Bag& bag)
{
  auto table = createEquipColumnTable(hero, bag);
  table.SelectAll().Border(LIGHT);
  table.SelectColumn(0).Border(LIGHT);
  table.SelectColumn(2).Border(LIGHT);
  table.SelectRow(0).Decorate(bold);
  table.SelectRow(0).SeparatorVertical(LIGHT);
  table.SelectRow(0).Border(DOUBLE);
  table.SelectRow(1).Border(LIGHT);
  return table.Render();
}



static
ftxui::Element getPriceTableElement(const Store& store)
{
  auto table = createPriceTable(store);
  table.SelectAll().Border(LIGHT);
  table.SelectColumn(0).Border(LIGHT);
  table.SelectColumn(2).Border(LIGHT);
  table.SelectRow(0).Decorate(bold);
  table.SelectRow(0).SeparatorVertical(LIGHT);
  table.SelectRow(0).Border(DOUBLE);
  return table.Render();
}

void Store::trade(Bag& bag, Hero& hero)
{
  auto screen = ScreenInteractive::FitComponent();
  auto closeFunc = screen.ExitLoopClosure();
  
  int value = 1;
  Component component;


  // clang-format off
  auto btn_dec_01 = Button("-1", [&] { if(value<=1) return; value -= 1; }, Style());
  auto btn_inc_01 = Button("+1", [&] { value += 1; }, Style());
  auto btn_dec_10 = Button("-10", [&] { if(value<=10) return;value -= 10; }, Style());
  auto btn_inc_10 = Button("+10", [&] { value += 10; }, Style());
  auto btn0 = Button("退出", [&] {closeFunc();}, Style());
  std::string str = "Welcome! 请选择购买或者出售 ";
  std::string str1 = " ";
  std::string selectMode = "购买";
  std::string selectedBtn = "LifeMedicine";
  auto btn1 = Button("购买", [&] {str="请选择要购买的商品";selectMode = "购买";}, Style());
  auto btn2 = Button("出售", [&] {str="请选择要出售的商品";selectMode = "出售";}, Style());
  auto btn3 = Button("刷新商店", [this] {
    this->refresh();
    }, Style());
  auto btn4 = Button("确定", [&] {
    if(hasEnding(selectedBtn,"edicine"))
    {
        std::shared_ptr<Medicine> MP;
        auto func = medicinebagmap[selectedBtn];
        func(MP);
        if(selectMode == "购买" &&  this->sold(MP,value,bag,hero))
        {
          str = selectMode + "成功";
        }
        else if(selectMode == "出售" &&  this->buy(MP,value,bag,hero))
        {
          str = selectMode + "成功";
        }
        else
        {
          str = selectMode + "失败";
        }
        
    }
    else
    {
        std::shared_ptr<Equip> EP;
        auto func = equipbagmap[selectedBtn];
        func(EP);
        if(selectMode == "购买" &&  this->sold(EP,value,bag,hero))
        {
          str = selectMode + "成功";
        }
        else if(selectMode == "出售" &&  this->buy(EP,value,bag,hero))
        {
          str = selectMode + "成功";
        }
        else
        {
          str = selectMode + "失败";
        }
    }
                        },Style());

  
  #define ItemButton(s,str1) Button(s,[&]{\
    selectedBtn = s;\
    if(hasEnding(selectedBtn,"edicine"))\
    {\
        std::shared_ptr<Medicine> MP;\
        auto func = medicinebagmap[selectedBtn];\
        func(MP);\
        str1 = MP->display();\
    }\
    else if(hasEnding(selectedBtn,"Armhour"))\
    {\
        std::shared_ptr<Equip> EP;\
        auto func = equipbagmap[selectedBtn];\
        func(EP);\
        if(EP->name == selectedBtn)\
        {\
            str1 = "hp "+formatCurrency(EP->hp)+" mp " +formatCurrency(EP->mp) +" 防御力 "+ formatCurrency(EP->def);\
        }\
    }\
    else if(hasEnding(selectedBtn,"Shoes"))\
    {\
        std::shared_ptr<Equip> EP;\
        auto func = equipbagmap[selectedBtn];\
        func(EP);\
        if(EP->name == selectedBtn)\
        {\
            str1 = "hp "+formatCurrency(EP->hp)+" mp " +formatCurrency(EP->mp) +" 防御力 "+ formatCurrency(EP->def);\
        }\
    }\
    else\
    {\
        str1 = "";\
    }\
  },Style());\


  auto Commodity1 = ItemButton("LifeMedicine",str1)
  auto Commodity2 = ItemButton("LifeResortingMedicine",str1)
  auto Commodity3 = ItemButton("SoulRevivingMedicine",str1)
  auto Commodity5 = ItemButton("SpiritConcentratingMedicine",str1)
  auto Commodity4 = ItemButton("HeavenlyOriginMedicine",str1)
  auto Commodity6 = ItemButton("IronSword",str1)
  auto Commodity7 = ItemButton("GreenSword",str1)
  auto Commodity8 = ItemButton("CrystalIceArmhour",str1)
  auto Commodity9 = ItemButton("BlazeArmhour",str1)
  auto Commodity10 = ItemButton("SwiftShoes",str1)
  auto Commodity11 = ItemButton("ThunderLightingShoes",str1)
  // clang-format on

  // The tree of components. This defines how to navigate using the keyboard.
  // The selected `row` is shared to get a grid layout.
  int row = 0;
  auto buttons = Container::Vertical({
      
      Container::Horizontal({btn1,btn2}, &row) | flex,      
      Container::Horizontal({btn_dec_01, btn_inc_01}, &row) | flex,
      Container::Horizontal({btn_dec_10, btn_inc_10}, &row) | flex,      
      Container::Horizontal({Commodity1,Commodity2,Commodity3,Commodity4}, &row)  | flex,      
      Container::Horizontal({Commodity5,Commodity6,Commodity7,Commodity8}, &row)  | flex,
      Container::Horizontal({Commodity9,Commodity10,Commodity11}, &row)  | flex,
      Container::Horizontal({btn4,btn3,btn0}, &row)  | flex,

  });

  // int row1 = 0;
  // auto buttons1 = Container::Vertical({
  //     Container::Horizontal({btn0, btn1}, &row1) | flex,
  //     Container::Horizontal({btn2, btn3}, &row1) | flex,
  // });

  // Modify the way to render them on screen:
  component = Renderer(buttons, [&, this] {
    return hbox({
        vbox({
               text("商店"),
               separator(),
               text(str),
               
               separator(),
               text(selectedBtn + " 数量: " + std::to_string(value)),
               text(str1),
               separator(),
               buttons->Render() | flex,
           }) |
           flex | border,
           vbox({
                getPriceTableElement(*this),
           })
           ,
           vbox({
                getBagTableElement(hero, bag),
                getEquipColumnTableElement(hero, bag) 
           }),

           filler()
    });
  });


  screen.Loop(component);

  std::cout << "商店关闭" << std::endl;
  ms_sleep(1000);
}


void Bag::displayEquipColumnAndChange(Hero& hero)
{
    auto screen = ScreenInteractive::FitComponent();
    auto closeFunc = screen.ExitLoopClosure();
    Component component;

    std::string selectedBtn = "WoodenSword";
    std::string str = "请选择要更换的装备";
    std::string str1;


    auto Equip1 = ItemButton("WoodenSword",str1)
    auto Equip2 = ItemButton("IronSword",str1)
    auto Equip3 = ItemButton("GreenSword",str1)
    auto Equip4 = ItemButton("HeavenlySword",str1)
    auto Equip5 = ItemButton("ClothArmhour",str1)
    auto Equip6 = ItemButton("CrystalIceArmhour",str1)
    auto Equip7 = ItemButton("BlazeArmhour",str1)
    auto Equip8 = ItemButton("HeavenlyDemonArmhour",str1)
    auto Equip9 = ItemButton("SwiftShoes",str1)
    auto Equip10 = ItemButton("ThunderLightingShoes",str1)
    auto Equip11 = ItemButton("ShadowShoes",str1)

    
    auto btn = Button("确定", [&] {
        std::shared_ptr<Equip> EP;
        auto func = equipbagmap[selectedBtn];
        func(EP);
        bool find = false;
        for(auto& i : equipBag)
        {
            if(EP->name == i.first->name )
            {
                find = true;
            }
        }
        if(find)
        {
          str = "装备成功";
          this->changeequip(EP,hero);
        }
        else
        {
          str = "装备失败，背包没有这个装备";
        }
                        },Style());

    auto btn1 = Button("退出", [&] {closeFunc();}, Style());
    int row = 0;
    auto buttons = Container::Vertical({
          
        Container::Horizontal({Equip1,Equip2,Equip3,Equip4}, &row)  | flex,      
        Container::Horizontal({Equip5,Equip6,Equip7,Equip8}, &row)  | flex,
        Container::Horizontal({Equip9,Equip10,Equip11}, &row)  | flex,
        Container::Horizontal({btn,btn1}, &row)  | flex,

    });

    component = Renderer(buttons, [&, this] {
    return hbox({
        vbox({
               text("更换装备"),
               separator(),
               text(str),
               text(str1),
               separator(),
               buttons->Render() | flex,
           }) |
           flex | border,
           vbox({
                getBagTableElement(hero, *this),
                getEquipColumnTableElement(hero,*this), 
           }),
    });
  });

  screen.Loop(component);
}

