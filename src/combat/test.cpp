
#include "../../include/combat.h"
#include "../../include/equip.h"
#include "../../lib/nterm.h"

#include <memory>  // for shared_ptr, __shared_ptr_access
#include <string>  // for operator+, to_string

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border

#include <iostream>

//using namespace ftxui;

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

int main()
{
    ntermInit();
    /*#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #*/
    srand((unsigned int)time(NULL));
    Skill s2("凌天一斩", "奋力向对方发动一次斩击。 ", 40, 20);
    Hero h;
    h.setName();
    h.setSkill(s2);
    std::shared_ptr<RedMedicine> redMedicine = std::make_shared<RedMedicine>() ;
    h.getBag().get(redMedicine,10);
    fightTunnel(&h);



//     int value = 0;

//     auto screen = ScreenInteractive::FitComponent();
//     auto closeFunc = screen.ExitLoopClosure();

//   // clang-format off
//   //-1 战斗
//     auto btn_dec_01 = Button("攻击", [&] { value += 1;  closeFunc();}, Style());
//   //1 逃跑
//   auto btn_inc_01 = Button("技能", [&] { value += 2;   closeFunc();}, Style());
//   auto btn_dec_10 = Button("物品", [&] { value += 3;   closeFunc();}, Style());
//   auto btn_inc_10 = Button("逃跑", [&] { value += 4;   closeFunc();}, Style());
//   // clang-format on

//   // The tree of components. This defines how to navigate using the keyboard.
//   // The selected `row` is shared to get a grid layout.
//   int row = 0;
//   auto buttons = Container::Vertical({
//       Container::Horizontal({btn_dec_01, btn_inc_01,btn_dec_10, btn_inc_10}, &row) | flex,
//       //Container::Horizontal({btn_dec_10, btn_inc_10}, &row) | flex,
//   });
//   // Modify the way to render them on screen:
//   auto component = Renderer(buttons, [&] {
//     return vbox({
//                //text("value = " + std::to_string(value)),
//                text("请选择"),
//                separator(),
//                buttons->Render() | flex,
//            }) |
//            flex | border;
//   });


//   screen.Loop(component);
//   std::cout<<value;
    return 0;
}
