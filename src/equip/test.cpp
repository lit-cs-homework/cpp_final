
#include "../../include/equip.h"

#include<memory>

// void fun()
// {
    // BlueMedicine bluemedicine;
    // RedMedicine redMedicine;
    // Stonesword a(0,0,0,10,10);
    // Ironsword b(0,0,0,30,30);
    // Bronzesword c(0,0,0,20,20);
    // Shoes d(5,5,5,10);
    // Armhour e(10,10,20,30);
    // std::vector<Equip> equipstore = {a,b,c};
    // std::vector<Medicine> medicinestore = {redMedicine,bluemedicine};
    // Store store(equipstore,medicinestore);
    // Hero hero;
    // Bag bag;
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


int main()
{
  /*
    using Ty = std::vector<std::shared_ptr<int>>;
    Ty ls;
    ls.push_back(std::make_shared<int>(6));
    auto ser = hps::to_string(ls);
    auto par = hps::from_string<Ty>(ser);
    assert (ls==par);
    return 0;
  */
    ntermInit();
    std::shared_ptr<BlueMedicine> bluemedicine = std::make_shared<BlueMedicine>() ;
    std::shared_ptr<RedMedicine> redMedicine = std::make_shared<RedMedicine>() ;
    std::shared_ptr<StoneSword> a = std::make_shared<StoneSword>  ();
    std::shared_ptr<IronSword> b = std::make_shared<IronSword>    ();
    std::shared_ptr<BronzeSword> c= std::make_shared<BronzeSword> ();
    std::shared_ptr<Shoes> d = std::make_shared<Shoes> (10, 20, 5,10);
    std::shared_ptr<Armhour> e = std::make_shared<Armhour> (20, 20, 20,30);
    std::vector<std::shared_ptr<Equip>> equipstore = {a,b,c};
    std::vector<std::shared_ptr<Medicine>> medicinestore = {redMedicine,bluemedicine};
    Store store(equipstore,medicinestore);
    Hero hero;
    hero.getBag().get(a,1);
    store.trade(hero.getBag(),hero);
    hero.getBag().display();
}

/*
#include <memory>  // for shared_ptr, __shared_ptr_access
#include <string>  // for operator+, to_string

#include "../../lib/ftxui/include/ftxui/component/captured_mouse.hpp"  // for ftxui
#include "../../lib/ftxui/include/ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "../../lib/ftxui/include/ftxui/component/component_base.hpp"      // for ComponentBase
#include "../../lib/ftxui/include/ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "../../lib/ftxui/include/ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border

using namespace ftxui;

// This is a helper function to create a button with a custom style.
// The style is defined by a lambda function that takes an EntryState and
// returns an Element.
// We are using `center` to center the text inside the button, then `border` to
// add a border around the button, and finally `flex` to make the button fill
// the available space.
ButtonOption Style() {
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

int main() {
  int value = 50;

  // clang-format off
  auto btn_dec_01 = Button("-1", [&] { value -= 1; }, Style());
  auto btn_inc_01 = Button("+1", [&] { value += 1; }, Style());
  auto btn_dec_10 = Button("-10", [&] { value -= 10; }, Style());
  auto btn_inc_10 = Button("+10", [&] { value += 10; }, Style());
  // clang-format on

  // The tree of components. This defines how to navigate using the keyboard.
  // The selected `row` is shared to get a grid layout.
  int row = 0;
  auto buttons = Container::Vertical({
      Container::Horizontal({btn_dec_01, btn_inc_01}, &row) | flex,
      Container::Horizontal({btn_dec_10, btn_inc_10}, &row) | flex,
  });

  // Modify the way to render them on screen:
  auto component = Renderer(buttons, [&] {
    return vbox({
               text("value = " + std::to_string(value)),
               separator(),
               buttons->Render() | flex,
           }) |
           flex | border;
  });

  auto screen = ScreenInteractive::FitComponent();
  screen.Loop(component);
  return 0;
}
*/