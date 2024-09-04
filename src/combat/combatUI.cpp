#include "../../include/combat.h"
#include "../../include/equip.h"
#include "../../include/utils.h"

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

Element gaugeLeft(float progress) {
  return gaugeDirection(progress, Direction::Left);
}

static
ftxui::Table createMedicineTable(const Hero& hero,const Bag& bag)
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
    for(const auto& p: bag.medicineBag) add(p);
    return Table(vec);
}

static
ftxui::Element getMedicineTableElement(const Hero& hero,const Bag& bag)
{
  auto table = createMedicineTable(hero, bag);
  table.SelectAll().Border(LIGHT);
  table.SelectColumn(0).Border(LIGHT);
  table.SelectColumn(2).Border(LIGHT);
  table.SelectRow(0).Decorate(bold);
  table.SelectRow(0).SeparatorVertical(LIGHT);
  table.SelectRow(0).Border(DOUBLE);
  table.SelectRow(0).Border(DOUBLE);
  return table.Render();
}

Hero hero;
Enemy enemy;
std::string str;
std::string str1;
bool end;
static
void fun(Hero& player,Enemy enemy,Skill& skill)
{
    str = "你对" + enemy.getName() + "使用了技能--" + skill.getName() + ".";
    // ms_sleep(1000);
    player.adjustMp(-skill.getMagicLose());
    if (enemy.getDefend() > skill.getHarm())
    {
        str1 = enemy.getName() + "抵挡住了你的攻击。";
        // ms_sleep(1000);
    }
    else
    {
        str1 = "你对" + enemy.getName() + "造成了" + std::to_string(skill.getHarm() - enemy.getDefend()) + "点伤害。";
        // ms_sleep(1000);
        enemy.adjustHp(enemy.getDefend() - skill.getHarm());
        if (enemy.getHp() <= 0 || player.getHp() <= 0)
	    {
		    end = true;
	    }
	    else
        {
            end = false;
        };
    }
}


int main()
{
    auto screen = ScreenInteractive::FitComponent();
    auto closeFunc = screen.ExitLoopClosure();
    Component component;

    auto btn0 = Button("普通攻击",[&]{
        str = "你对" + enemy.getName() + "进行了攻击。";
		if (enemy.getDefend() > hero.getAttack())
		{
			str1 = enemy.getName() + "抵挡住了你的攻击。";
			// ms_sleep(1000);
		}
		else
		{
			str1 = "你对" + enemy.getName() + "造成了" +std::to_string(hero.getAttack() - enemy.getDefend())+ "点伤害。";
			// ms_sleep(1000);
			enemy.adjustHp(enemy.getDefend() - hero.getAttack());
            if (enemy.getHp() <= 0 || hero.getHp() <= 0)
	        {
		        end = true;
	        }
	        else
            {
                end = false;
            };
		}
    },Style());

    auto btn1 = Button("尝试逃跑",[&]{
        if (enemy.getThreaten() < 3)
		{
			str = "逃跑失败" ;
		}
		else
		{
			if (rand() % 6 < enemy.getThreaten())
			{
				str = "逃跑成功" ;
                closeFunc();
			}
            else
            {
                str = "逃跑失败" ;
            }
		}
    },Style());

    std::vector<ftxui::Component> skill;
    skill.push_back(Button("当前没有技能可用",[]{},Style()));

    if(hero.getskills().size() != 0) skill.clear();

    for(int i=0;i<hero.getskills().size();i++)
    {
        skill.push_back(Button(hero.getskills()[i].getName(),[&]{
            if(hero.getskills()[i].getMagicLose() > hero.getMp())
            {
                str = "当前魔法不足，请重新选择";
            }
            else
            {
                (hero,enemy,hero.getskills()[i]);
            }
        },Style()));
    }

    std::vector<ftxui::Component> medicine;
    for(auto& i: hero.getBag().medicineBag)
    {
        if(i.first != nullptr)
        skill.push_back(Button(i.first->name,[&]{
            if(hero.use(i.first,1))
            {
                str = "使用成功" ;
            }
            else
            {
                str = "使用失败" ;
            } 
        },Style()));
    }

    int row = 0;
    auto buttons = Container::Vertical({ 
      Container::Horizontal({btn0}, &row) | flex,
      Container::Horizontal(skill, &row) | flex,
      Container::Horizontal(medicine, &row) | flex,      
      Container::Horizontal({btn1}, &row)  | flex,
  });

    component = Renderer(buttons, [&] {
        return hbox({
            vbox({
                    gauge(0.5),
                    separator(),
                    text(str),
                    separator(),
                    separator(),
                    buttons->Render() | flex,
                }) |
                flex | border,
                vbox({
                })
                ,
                vbox({
                }),

                filler()
        });
    });


  screen.Loop(component);
}
