
#include "../../include/equip.h"

#include<memory>

// void fun()
// {
//     BlueMedicine bluemedicine;
//     RedMedicine redMedicine;
//     Stonesword a(0,0,0,10,10);
//     Ironsword b(0,0,0,30,30);
//     Bronzesword c();
//     Shoes d(5,5,5,10);
//     Armhour e(10,10,20,30);
//     std::vector<Equip> equipstore = {a,b,c};
//     std::vector<Medicine> medicinestore = {redMedicine,bluemedicine};
//     Store store(equipstore,medicinestore);
//     Hero hero;
//     Bag bag;
// }

#include <memory>



// template <class T, class B>
// class Serializer<std::shared_ptr<T>, B> {
//  public:
//   static void serialize(const std::shared_ptr<T>& container, B& ob) {
//     if (container) {
//       ob.write_char(1);
//       Serializer<T, B>::serialize(*container, ob);
//     } else {
//       ob.write_char(0);
//     }
//   }

//   static void parse(std::shared_ptr<T>& container, B& ib) {
//     if (ib.read_char()) {
//       if (!container) {
//         container.reset(new T());
//       }
//       Serializer<T, B>::parse(*container, ib);
//     } else {
//       container.reset(nullptr);
//     }
//   }
// };

extern
  std::unordered_map<
      std::string,
      std::function<void(std::shared_ptr<Equip>&)>
  > equipbagmap;
extern
  std::unordered_map<
      std::string,
      std::function<void(std::shared_ptr<Medicine>&)>
  > medicinebagmap;

// extern
//     std::unordered_map<
//     std::string,
//     std::function<void(std::shared_ptr<Equip>&)>
//     > equipcolumnmap;

// int main()
// {
//   /*
//     using Ty = std::vector<std::shared_ptr<int>>;
//     Ty ls;
//     ls.push_back(std::make_shared<int>(6));
//     auto ser = hps::to_string(ls);
//     auto par = hps::from_string<Ty>(ser);
//     assert (ls==par);
//     return 0;
//   */

//     ntermInit();
//     Store store;
//     Hero hero;
//     store.refresh();
//     store.display();
//     store.trade(hero.getBag(),hero);
//   //  for(const auto& p: equipbagmap) {
//   //      std::cout << p.first << std::endl;

//   //  }
//   //  for(const auto& p: medicinebagmap) {
//   //      std::cout << p.first << std::endl;

//   //  }
//   //  auto str = hps::to_string(bag);
//   //  auto nbag = hps::from_string<Bag>(str);
//   // auto str2 = hps::to_string(store);
//   // auto nstore = hps::from_string<Store>(str2);
//   // auto str1 = hps::to_string(hero);
//   // auto nhero = hps::from_string<Hero>(str1);
//   // //  bag.display();
//   // //  std::cout << std::endl;
//   // //  nbag.display();
//   // hero.showHero();
//   // std::cout<<hero.getGold() <<std::endl;
//   // hero.getBag().display();
//   // store.display();
//   // std::cout << std::endl;
//   // nhero.showHero();
//   // std::cout<<nhero.getGold() <<std::endl;
//   // nhero.getBag().display();
//   // nstore.display();



//    return 0;
// }


// #include <memory>  // for shared_ptr, __shared_ptr_access
// #include <string>  // for operator+, to_string

// #include "../../lib/ftxui/include/ftxui/component/captured_mouse.hpp"  // for ftxui
// #include "../../lib/ftxui/include/ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
// #include "../../lib/ftxui/include/ftxui/component/component_base.hpp"      // for ComponentBase
// #include "../../lib/ftxui/include/ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
// #include "../../lib/ftxui/include/ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border

// using namespace ftxui;

// This is a helper function to create a button with a custom style.
// The style is defined by a lambda function that takes an EntryState and
// returns an Element.
// We are using `center` to center the text inside the button, then `border` to
// add a border around the button, and finally `flex` to make the button fill
// the available space.
// ButtonOption Style() {
//   auto option = ButtonOption::Animated();
//   option.transform = [](const EntryState& s) {
//     auto element = text(s.label);
//     if (s.focused) {
//       element |= bold;
//     }
//     return element | center | borderEmpty | flex;
//   };
//   return option;
// }


int main() {
  ntermInit();
  std::shared_ptr<Medicine> __ = std::make_shared<Medicine>();
  std::shared_ptr<IronSword> a = std::make_shared<IronSword>();
  std::shared_ptr<LifeMedicine> redMedicine = std::make_shared<LifeMedicine>();
  Store store;
  // 
  store.refresh();
  Hero hero;
  hero.adjustGold(50);
  hero.getBag().get(a,1);
  hero.getBag().get(redMedicine,2);
  // hero.getBag().displayEquipColumnCil(hero);
  store.trade(hero.getBag(),hero);
  hero.getBag().displayEquipColumnAndChange(hero);
  return 0;
  // ntermInit();
  // auto screen = ScreenInteractive::FitComponent();
  // auto closeFunc = screen.ExitLoopClosure();
  
  // int value = 1;
  // Store store;
  // store.refresh();
  // Hero hero;
  // Component component;


  // // clang-format off
  // auto btn_dec_01 = Button("-1", [&] { if(value<=1) return; value -= 1; }, Style());
  // auto btn_inc_01 = Button("+1", [&] { value += 1; }, Style());
  // auto btn_dec_10 = Button("-10", [&] { if(value<=10) return;value -= 10; }, Style());
  // auto btn_inc_10 = Button("+10", [&] { value += 10; }, Style());
  // auto btn0 = Button("退出", [&] {closeFunc();}, Style());
  // std::string str = "welcome";
  // std::string selectMode = "购买";
  // std::string selectedBtn = "BlueMedicine";
  // auto btn1 = Button("购买", [&] {str="请选择要购买的商品";selectMode = "购买";}, Style());
  // auto btn2 = Button("出售", [&] {str="请选择要出售的商品";selectMode = "出售";}, Style());
  // auto btn3 = Button("刷新商店",[&] {store.refresh();}, Style());
  // auto btn4 = Button("确定", [&] {
  //   if(hasEnding(selectedBtn,"edicine"))
  //   {
  //       std::shared_ptr<Medicine> MP;
  //       auto func = medicinebagmap[selectedBtn];
  //       func(MP);
  //       if(store.sold(MP,value,hero.getBag(),hero) && selectMode == "购买")
  //       {
  //         str = selectMode + "成功";
  //       }
  //       else if(store.buy(MP,value,hero.getBag(),hero) && selectMode == "出售")
  //       {
  //         str = selectMode + "成功";
  //       }
  //       else
  //       {
  //         str = selectMode + "失败";
  //       }
        
  //   }
  //   else
  //   {
  //       std::shared_ptr<Equip> EP;
  //       auto func = equipbagmap[selectedBtn];
  //       func(EP);
  //       if(store.sold(EP,value,hero.getBag(),hero) && selectMode == "购买")
  //       {
  //         str = selectMode + "成功";
  //       }
  //       else if(store.buy(EP,value,hero.getBag(),hero) && selectMode == "出售")
  //       {
  //         str = selectMode + "成功";
  //       }
  //       else
  //       {
  //         str = selectMode + "失败";
  //       }
  //   }
  //                       },Style());

  
  // #define ItemButton(s,str) Button(s,[&]{selectedBtn = s;str="请选择该商品的数量";},Style());
  // auto Commodity1 = ItemButton("BlueMedicine",str)
  // auto Commodity2 = ItemButton("RedMedicine",str)
  // auto Commodity3 = ItemButton("StoneSword",str)
  // auto Commodity4 = ItemButton("BrozenSword",str)
  // auto Commodity5 = ItemButton("IronSword",str)
  // auto Commodity6 = ItemButton("Armhour",str)
  // auto Commodity7 = ItemButton("Shoes",str)
  // // clang-format on

  // // The tree of components. This defines how to navigate using the keyboard.
  // // The selected `row` is shared to get a grid layout.
  // int row = 0;
  // auto buttons = Container::Vertical({
      
  //     Container::Horizontal({btn1,btn2}, &row) | flex,      
  //     Container::Horizontal({btn_dec_01, btn_inc_01}, &row) | flex,
  //     Container::Horizontal({btn_dec_10, btn_inc_10}, &row) | flex,      
  //     Container::Horizontal({Commodity1,Commodity2,Commodity3}, &row)  | flex,      
  //     Container::Horizontal({Commodity5,Commodity6,Commodity4}, &row)  | flex,
  //     Container::Horizontal({Commodity7}, &row)  | flex,
  //     Container::Horizontal({btn4,btn3,btn0}, &row)  | flex,

  // });

  // // int row1 = 0;
  // // auto buttons1 = Container::Vertical({
  // //     Container::Horizontal({btn0, btn1}, &row1) | flex,
  // //     Container::Horizontal({btn2, btn3}, &row1) | flex,
  // // });

  // // Modify the way to render them on screen:
  // component = Renderer(buttons, [&] {
  //   return vbox({
  //              text("商店"),
  //              separator(),
  //              text(str),
  //              separator(),
  //              text(selectedBtn + " 数量: " + std::to_string(value)),
  //              separator(),
  //              buttons->Render() | flex,
  //          }) |
  //          flex | border
  // ;});

  // screen.Loop(component);
  
  // return 0;
}