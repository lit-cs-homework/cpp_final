
#include "../../include/combat.h"

#include "../../include/equip.h"
#include "../../lib/nterm.h"

#include <iostream>
// int main()
// {
//     ntermInit();
//     /*
//     #ifdef _WIN32
//     SetConsoleCP(CP_UTF8);
//     SetConsoleOutputCP(CP_UTF8);
//     #endif*/
//     srand((unsigned int)time(NULL));
//     Skill s2("凌天一斩", "奋力向对方发动一次斩击。 ", 40, 20);
//     Hero h;
//     h.setName();
//     h.setSkill(s2);
//     std::shared_ptr<RedMedicine> redMedicine = std::make_shared<RedMedicine>() ;
//     h.getBag().get(redMedicine,10);
//     //fightTunnel(&h);
//     std::cout<<"11";
//     cursorDown(1);
//     std::cout<<"22";
//     return 0;
// }

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
Skill s2("凌天一斩", "奋力向对方发动一次斩击。 ", 40, 20);
std::shared_ptr<RedMedicine> redMedicine = std::make_shared<RedMedicine>() ;
Enemy enemy("A","",100,100,0,0,10,5,4,5,1);
Skill s1("冲撞", "大凶兔气势汹汹的一击，威力不可小觑。", 20, 0);
Skill S1[1] = { s1 };
const char* const defVal = "                     ";
std::string str = defVal;
std::string str1 = defVal;
std::string str2 = defVal;
std::string str3 = defVal;

bool end = false;

static void enemyAttack(Hero& hero,Enemy& enemy);

static
void fun(Hero& player,Enemy& enemy,Skill& skill)
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
    if(end == false)
    {
        enemyAttack(player,enemy);
    }
}


void enemyAttack(Hero& hero,Enemy& enemy)
{
    int num = rand() % enemy.getSkillnum();
    if (enemy.getSkill(num).getMagicLose() <= enemy.getMp())
    {
        enemy.adjustMp(-enemy.getSkill(num).getMagicLose());
        int harm = enemy.getSkill(num).getHarm();

        str2 = enemy.getName() + "使用了" + enemy.getSkill(num).getName() + ".";
        // ms_sleep(1000);
        if (harm - hero.getDefend() > 0)
        {
            str3 = enemy.getName() + "对你造成了" + std::to_string(harm - hero.getDefend())  + "点伤害。";
            // ms_sleep(1000);
            hero.adjustHp(hero.getDefend() - harm);
        }
        else
        {
            str3 = "你成功抵御了" + enemy.getName() + "攻击。";
            // ms_sleep(1000);
        } 
    }
    else
    {
        enemyAttack(hero, enemy);
    }

}

int main()
{
    enemy.setSkill(S1,1);
    hero.setSkill(s2);
    hero.getBag().get(redMedicine,10);
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
        if(end == false)
        {
            enemyAttack(hero,enemy);
        }
        else
        {
            closeFunc();
            if (hero.getHp() <= 0)
            {
                std::cout << std::endl <<"战斗失败";
            }
            else if(enemy.getHp() <= 0 )
            {
                std::cout <<std::endl<< "战斗成功";
            }
            
        }
        
    },Style());

    auto btn1 = Button("尝试逃跑",[&]{
        if (enemy.getThreaten() < 3)
		{
			str = "逃跑失败" ;
            str1 = defVal;
            str2 = defVal;
            str3 = defVal;
		}
		else
		{
			if (rand() % 6 < enemy.getThreaten())
			{
				str = "逃跑成功" ;
                closeFunc();
                std::cout << str;
			}
            else
            {
                str = "逃跑失败" ;
                str1 = defVal;
                str2 = defVal;
                str3 = defVal;
            }
		}
    },Style());

    std::vector<ftxui::Component> skill;

    if(hero.getskills().size() == 0) skill.push_back(Button("当前没有技能可用",[]{},Style()));

    for(int i=0;i<hero.getskills().size();i++)
    {
        skill.push_back(Button(hero.getskills()[i].getName(),[&, i]{
            auto& sk = hero.getskills()[i];
            if(sk.getMagicLose() > hero.getMp())
            {
                str = "当前魔法不足，请重新选择";
                str1 = defVal;
                str2 = defVal;
                str3 = defVal;
            }
            else
            {
                fun(hero,enemy,sk);
            }
        },Style()));
    }

    std::vector<ftxui::Component> medicine;
    ;

    if(hero.getBag().medicineBag.size() == 0) medicine.push_back(Button("当前没有药水可用",[]{},Style()));
    for(auto& i: hero.getBag().medicineBag)
    {
        if(i.first != nullptr)
            medicine.push_back(Button(i.first->name,[&,i]{
            if(hero.use(i.first,1))
            {
                str = "使用成功" ;
                str1 = defVal;
                str2 = defVal;
                str3 = defVal;
            }
            else
            {
                str = "使用失败" ;
                str1 = defVal;
                str2 = defVal;
                str3 = defVal;
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

                }),
            vbox({
                    text("敌人血量:"+std::to_string(enemy.getHp())),
                    separator(),
                    gauge(enemy.getHp()/(double)enemy.getHpMax()),
                    text(str2),
                    text(str3),
                    separator(),
                    text("玩家血量:"+std::to_string(hero.getHp())) | align_right,
                    separator(),
                    gauge(hero.getHp()/(double)hero.getHpMax()),
                    separator(),
                    text(str),
                    text(str1),
                    separator(),
                    separator(),
                    buttons->Render() | flex,
                }) |
                flex | border,
                vbox({
                    getMedicineTableElement(hero,hero.getBag()),
                })
                ,
                vbox({
                }),

                filler()
        });
    });


  screen.Loop(component);
}

