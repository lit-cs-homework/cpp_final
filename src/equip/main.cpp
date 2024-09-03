
#include "../../include/equip.h"

#include "../../lib/ftxui/include/ftxui/component/captured_mouse.hpp"  // for ftxui
#include "../../lib/ftxui/include/ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "../../lib/ftxui/include/ftxui/component/component_base.hpp"      // for ComponentBase
#include "../../lib/ftxui/include/ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "../../lib/ftxui/include/ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border

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

void Bag::displayEquipColumn()
{
    std::cout << "装备栏:" << std::endl;
    for(const auto& i: equipColumn){
        if(i != nullptr){
            std::cout << i->typ() << "." << i->name << std::endl;
        } else {
            std::cout << "(none)" << std::endl;
        }
    }
    std::cout << "是否要更换装备" << std::endl;

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
    if(hero.hp < hero.hpMax){
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
    const char* const MapName##cls = __func__;\
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
    std::shared_ptr<BlueMedicine> bluemedicine = std::make_shared<BlueMedicine>() ;
    std::shared_ptr<RedMedicine> redMedicine = std::make_shared<RedMedicine>() ;
    std::shared_ptr<StoneSword> a = std::make_shared<StoneSword>  ();
    std::shared_ptr<IronSword> b = std::make_shared<IronSword>    ();
    std::shared_ptr<BronzeSword> c= std::make_shared<BronzeSword> ();
    std::shared_ptr<Shoes> d = std::make_shared<Shoes> (10, 20, 5,10);
    std::shared_ptr<Armhour> e = std::make_shared<Armhour> (20, 20, 20,30);
    std::vector<std::shared_ptr<Equip>> equipstore = {a,b,c};
    std::vector<std::shared_ptr<Medicine>> medicinestore = {redMedicine,bluemedicine};

    for (const auto& i : equipstore){
        equipCommodities.insert(std::make_pair(i, 1));   
    }
    for (const auto& i : medicinestore){
        medicineCommodities.insert(std::make_pair(i, 999));   
    }
}

void Store::trade(Bag& bag,Hero& hero){
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


#define ImplSword(cls,...) \
cls::cls(): Sword(__VA_ARGS__){\
    withName1(cls);\
}\

ImplSword(StoneSword , 10, 5)
ImplSword(BronzeSword, 20, 10)
ImplSword(IronSword  , 30, 15)


RetType(Armhour)

#define def4(cls) \
cls::cls(double value, double hp, double mp, double def): Equip(value, hp, mp, def){withName1(cls);}


#define ArmOrShoe(cls,...) def4(cls);\
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
}
RedMedicine::RedMedicine(){
    withName2(RedMedicine);
    hp = 10;
    mp = 0;
    value = 10;
}

void RedMedicine::display() const{
    std::cout << "hp回复" << std::endl;
}

BlueMedicine::BlueMedicine(){
    withName2(BlueMedicine);
    hp = 0;
    mp = 10;
    value = 10;
}

void BlueMedicine::display() const{
    std::cout << "mp回复" << std::endl;
}

bool hasEnding(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

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
void UIforStore()
{
  ntermInit();
  auto screen = ScreenInteractive::FitComponent();
  auto closeFunc = screen.ExitLoopClosure();
  
  int value = 1;
  Store store;
  store.refresh();
  Hero hero;
  Component component;


  // clang-format off
  auto btn_dec_01 = Button("-1", [&] { if(value<=1) return; value -= 1; }, Style());
  auto btn_inc_01 = Button("+1", [&] { value += 1; }, Style());
  auto btn_dec_10 = Button("-10", [&] { if(value<=10) return;value -= 10; }, Style());
  auto btn_inc_10 = Button("+10", [&] { value += 10; }, Style());
  auto btn0 = Button("退出", [&] {closeFunc();}, Style());
  std::string str = "welcome";
  std::string selectMode = "购买";
  std::string selectedBtn = "BlueMedicine";
  auto btn1 = Button("购买", [&] {str="请选择要购买的商品";selectMode = "购买";}, Style());
  auto btn2 = Button("出售", [&] {str="请选择要出售的商品";selectMode = "出售";}, Style());
  auto btn3 = Button("刷新商店",[&] {store.refresh();}, Style());
  auto btn4 = Button("确定", [&] {
    if(hasEnding(selectedBtn,"edicine"))
    {
        std::shared_ptr<Medicine> MP;
        auto func = medicinebagmap[selectedBtn];
        func(MP);
        if(store.sold(MP,value,hero.getBag(),hero) && selectMode == "购买")
        {
          str = selectMode + "成功";
        }
        else if(store.buy(MP,value,hero.getBag(),hero) && selectMode == "出售")
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
        if(store.sold(EP,value,hero.getBag(),hero) && selectMode == "购买")
        {
          str = selectMode + "成功";
        }
        else if(store.buy(EP,value,hero.getBag(),hero) && selectMode == "出售")
        {
          str = selectMode + "成功";
        }
        else
        {
          str = selectMode + "失败";
        }
    }
                        },Style());

  
  #define ItemButton(s,str) Button(s,[&]{selectedBtn = s;str="请选择该商品的数量";},Style());
  auto Commodity1 = ItemButton("BlueMedicine",str)
  auto Commodity2 = ItemButton("RedMedicine",str)
  auto Commodity3 = ItemButton("StoneSword",str)
  auto Commodity4 = ItemButton("BrozenSword",str)
  auto Commodity5 = ItemButton("IronSword",str)
  auto Commodity6 = ItemButton("Armhour",str)
  auto Commodity7 = ItemButton("Shoes",str)
  // clang-format on

  // The tree of components. This defines how to navigate using the keyboard.
  // The selected `row` is shared to get a grid layout.
  int row = 0;
  auto buttons = Container::Vertical({
      
      Container::Horizontal({btn1,btn2}, &row) | flex,      
      Container::Horizontal({btn_dec_01, btn_inc_01}, &row) | flex,
      Container::Horizontal({btn_dec_10, btn_inc_10}, &row) | flex,      
      Container::Horizontal({Commodity1,Commodity2,Commodity3}, &row)  | flex,      
      Container::Horizontal({Commodity5,Commodity6,Commodity4}, &row)  | flex,
      Container::Horizontal({Commodity7}, &row)  | flex,
      Container::Horizontal({btn4,btn3,btn0}, &row)  | flex,

  });

  // int row1 = 0;
  // auto buttons1 = Container::Vertical({
  //     Container::Horizontal({btn0, btn1}, &row1) | flex,
  //     Container::Horizontal({btn2, btn3}, &row1) | flex,
  // });

  // Modify the way to render them on screen:
  component = Renderer(buttons, [&] {
    return vbox({
               text("商店"),
               separator(),
               text(str),
               separator(),
               text(selectedBtn + " 数量: " + std::to_string(value)),
               separator(),
               buttons->Render() | flex,
           }) |
           flex | border
  ;});

  screen.Loop(component);
}

