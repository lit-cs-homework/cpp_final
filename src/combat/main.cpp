
#include "../../include/combat.h"
#include "../../lib/nterm.h"

#include "../../include/utils.h"
#include "game.h"

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border
#include "ftxui/dom/node.hpp"
#include "ftxui/dom/elements.hpp"  // for color, Fit, LIGHT, align_right, bold, DOUBLE
#include "ftxui/dom/table.hpp"      // for Table, TableSelection
#include "ftxui/screen/screen.hpp"
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border
#include "ftxui/dom/node.hpp"
#include "ftxui/dom/elements.hpp"  // for color, Fit, LIGHT, align_right, bold, DOUBLE
#include "ftxui/dom/table.hpp"      // for Table, TableSelection
#include "ftxui/screen/screen.hpp"

using ftxui::Element;
using ftxui::Table;
using ftxui::center;
using ftxui::bold;
using ftxui::LIGHT;
using ftxui::ButtonOption;
using ftxui::EntryState;
using ftxui::text;
using ftxui::flex;
using ftxui::borderEmpty;
using ftxui::Component;
using ftxui::hbox;
using ftxui::vbox;
using ftxui::Render;
using ftxui::separator;
using ftxui::Renderer;
using ftxui::gauge;
using ftxui::align_right;
using ftxui::border;
using ftxui::filler;
using ftxui::ScreenInteractive;


// int ifFight()
// {
//   using namespace ftxui;
// 	int value = 0;
//     auto screen = ScreenInteractive::FitComponent();
//     auto closeFunc = screen.ExitLoopClosure();


//   //-1 战斗
//     auto btn_dec_01 = Button("战斗", [&] { value -= 1;  closeFunc();}, Style());
//   //1 逃跑
//   auto btn_inc_01 = Button("逃跑", [&] { value += 1;   closeFunc();}, Style());
//   int row = 0;
//   auto buttons = Container::Vertical({
//       Container::Horizontal({btn_dec_01, btn_inc_01}, &row) | flex,
//   });
//     auto component = Renderer(buttons, [&] {
//     return vbox({ text("请选择"),separator(),buttons->Render() | flex,}) |flex | border;});


//    screen.Loop(component);
//    return value;
// }


Skill::Skill() {}
Skill::Skill(std::string name, std::string introduce, int harm, int magicLose) :name(name), introduce(introduce), harm(harm), magicLose(magicLose) {}
Skill::~Skill() {}
void Skill::showSkill()
{
	std::cout << "--" << name << "--" << std::endl;
	std::cout << introduce << std::endl;
	std::cout << "伤害:" << harm << "  ";
	std::cout << "耗蓝:" << magicLose << std::endl;
}
std::string Skill::getName()
{
	return name;
}
std::string Skill::getIntroduce()
{
	return introduce;
}
int Skill::getHarm()
{
	return harm;
}
int Skill::getMagicLose()
{
	return magicLose;
}
//1级
Skill skill1("全力一击", "奋力向对方发动一次攻击。 ", 40, 20);
//3级
Skill skill2("剑气纵横", "向前方释放出一道锋利的剑气攻击敌人。", 100, 40);
//5级
Skill skill3("破甲突击", "剑尖对目标进行强力刺击。 ", 200, 100);
//8级
Skill skill4("凌天一斩", "以全身为媒介调用所有魂力发动一次斩击。 ", 500, 300);
//10级
Skill skill5("神天并地", "体内深藏的力量逐渐苏醒，通过燃烧魂力来终结敌人。 ", 12000, 3000);


Hero::Hero()
{
	//setName();
	hp = 100;
	hpMax = 100;
	mp = 50;
	mpMax = 50;
	attack = 30;
	defend = 10;
	skillNumber = 0;
	exp = 0;
	gold = 0;
	level = 1;
}
Hero::~Hero() {}
void Hero::setName()
{
	std::cout << "请设置您的昵称：";
	std::string tmpName;
	std::cin >> tmpName;
	name = tmpName;
	setSkill(skill1);
	eraseScreen();
}
void Hero::showHero()
{
	std::cout << "--" << name << "--" << std::endl;
	std::cout << "等级：" << level << "  ";
	std::cout << "经验：" << exp << "/" << expMax[level - 1] << "  ";
	std::cout << "hp：" << hp << "/" << hpMax << "  ";
	std::cout << "mp：" << mp << "/" << mpMax << "  ";
	std::cout << "攻击：" << attack << "  ";
	std::cout << "防御：" << defend << std::endl;
}
void Hero::addHp(int num)//增加生命上限
{
	hp += num;
	hpMax += num;
}
void Hero::adjustHp(int num)//增加或减少生命值
{
	hp += num;
}
void Hero::addMp(int num)//增加魔法上限
{
	mp += num;
	mpMax += num;
}
void Hero::adjustMp(int num)//增加或减少魔法值
{
	mp += num;
}
void Hero::adjustAttack(int num)
{
	attack += num;
}
void Hero::adjustDefend(int num)
{
	defend += num;
}
void Hero::addExp(int num)
{
	exp += num;
	while (exp >= expMax[level - 1] && level < 10)
	{
		exp -= expMax[level - 1];
		level++;
		std::cout << "恭喜你升到了" << level << "级！" << std::endl;
		addHp(20*level);
		addMp(20*level);
		adjustAttack(5*level);
		adjustDefend(5);
		switch(level)
		{
			case 3:
			{
				std::cout << "你领悟到了新技能：" << skill2.getName() << std::endl;
				setSkill(skill2);
				break;
			}
			case 5:
			{
				std::cout << "你领悟到了新技能：" << skill3.getName() << std::endl;
				setSkill(skill3);
				break;
			}
			case 8:
			{
				std::cout << "你领悟到了新技能：" << skill4.getName() << std::endl;
				setSkill(skill4);
				break;
			}
			case 10:
			{
				std::cout << "你领悟到了新技能：" << skill5.getName() << std::endl;
				setSkill(skill5);
				break;
			}
		}
	}
}
void Hero::adjustGold(int num)
{
	gold += num;
}
int Hero::getHp()
{
	return hp;
}
int Hero::getHpMax()
{
	return hpMax;
}
int Hero::getMp()
{
	return mp;
}

int Hero::getAttack()
{
	return attack;
}
int Hero::getDefend()
{
	return defend;
}
int Hero::getExp()
{
	return exp;
}
int Hero::getGold()
{
	return gold;
}
int Hero::getLevel()
{
	return level;
}
Bag& Hero::getBag()
{
	return bag;
}
std::unordered_map<std::shared_ptr<Medicine>,int, hashBaseEquip,eqOnObj>& Hero::getMedicine()
{
	return bag.medicineBag;
}
void Hero::setSkill(Skill skill)
{
	skills.push_back(skill);
}
std::vector<Skill>& Hero::getskills()
{
	return skills;
}
bool Hero::use(std::shared_ptr<Medicine> medicine, int n){
    return bag.use(medicine, n, *this);
}
//void Hero::changeequip(std::shared_ptr<Equip> equip){
//    bag.changeequip(equip, *this);
//}



Enemy::Enemy() {}
Enemy::Enemy(std::string name, std::string introduce, int hp, int hpMax, int mp, int mpMax, int attack, int defend, int threaten, int exp, int gold) : name(name), introduce(introduce), hp(hp), hpMax(hpMax), mp(mp), mpMax(mpMax), attack(attack), defend(defend), threaten(threaten), exp(exp), gold(gold)
{
	;
}
Enemy::~Enemy() {}
void Enemy::showEnemy()
{
	std::cout << "--" << name << "--" << std::endl;
	//std::cout << introduce << std::endl;
	std::cout << "hp：" << hp << "/" << hpMax << "  ";
	std::cout << "mp：" << mp << "/" << mpMax << "  ";
	std::cout << "攻击：" << attack << "  ";
	std::cout << "防御：" << defend << "  ";
	std::cout << "威胁指数：";
	for (int i = 1; i <= threaten; i++) std::cout << "*";
	std::cout << std::endl;
}
void Enemy::adjustHp(int num)//增加或减少生命值
{
	hp += num;
}
void Enemy::adjustMp(int num)//增加或减少魔法值
{
	mp += num;
}
void Enemy::adjustAttack(int num)
{
	attack += num;
}
void Enemy::adjustDefend(int num)
{
	defend += num;
}
std::string Enemy::getName()
{
	return name;
	
}
std::string Enemy::getIntroduce()
{
	return introduce;
}

int Enemy::getHp()
{
	return hp;
}
int Enemy::getHpMax()
{
	return hpMax;
}

int Enemy::getMp()
{
	return mp;
}
int Enemy::getAttack()
{
	return attack;
}
int Enemy::getDefend()
{
	return defend;
}
int Enemy::getSkillnum()
{
	return (int)skills.size();
}
Skill Enemy::getSkill(int pos)
{
	return skills[pos];
}
int Enemy::getThreaten()
{
	return threaten;
}
int Enemy::getExp()
{
	return exp;
}
int Enemy::getGold()
{
	return gold;
}
void Enemy::setSkill(Skill skill[], int num)//设置技能
{
	for (int i = 0; i < num; i++)
	{
		skills.push_back(skill[i]);
	}
}


Battle::Battle(Hero* hero, Enemy enemy) :player(hero), enemy(enemy)//构造
{
	round = 1;
	fight1(*player,enemy);
	//fight();
}
Battle::~Battle() {}
void Battle::showRound()//回合演示
{
	std::cout << "----回合" << round << "----" << std::endl;
	ms_sleep(500);
	(*player).showHero();
	std::cout<<std::endl;
	ms_sleep(1000);
	enemy.showEnemy();
	ms_sleep(1000);
}

int Battle::playerRound()
{
	// using namespace ftxui;
	// int value = 0;

    // auto screen = ScreenInteractive::FitComponent();
    // auto closeFunc = screen.ExitLoopClosure();

    // auto btn_dec_01 = Button("攻击", [&] { value += 1;  closeFunc();}, Style());
	// auto btn_inc_01 = Button("技能", [&] { value += 2;   closeFunc();}, Style());
 	// auto btn_dec_10 = Button("物品", [&] { value += 3;   closeFunc();}, Style());
  	// auto btn_inc_10 = Button("逃跑", [&] { value += 4;   closeFunc();}, Style());
 
  	// int row = 0;
    // auto buttons = Container::Vertical({
    // Container::Horizontal({btn_dec_01, btn_inc_01,btn_dec_10, btn_inc_10}, &row) | flex, });
    // auto component = Renderer(buttons, [&] {
    // return vbox({text("请选择"),separator(),buttons->Render() | flex,}) |flex | border; });


    // screen.Loop(component);
	std::cout<<"请选择：1.攻击 2.技能 3.物品 4.逃跑"<<std::endl;
	int value=getch();
	switch (value)
	{
	case '1'://攻击
	{
		std::cout << "你对" << enemy.getName() << "进行了攻击。" << std::endl;
		ms_sleep(1000);
		if (enemy.getDefend() > (*player).getAttack())
		{
			std::cout << enemy.getName() << "抵挡住了你的攻击。" << std::endl;
			ms_sleep(1000);
		}
		else
		{
			std::cout << "你对" << enemy.getName() << "造成了" << (*player).getAttack() - enemy.getDefend() << "点伤害。" << std::endl;
			ms_sleep(1000);
			enemy.adjustHp(enemy.getDefend() - (*player).getAttack());
		}
		return -1;
	}
	case '2'://使用技能
	{
		if((*player).getskills().size()==0)
		{
			std::cout<<"当前没有技能可用！"<<std::endl;
			playerRound();
			return -1;
		}
		for (int i = 1; i <= (*player).getskills().size(); i++)
		{
			std::cout << i << "." << (*player).getskills()[i - 1].getName() << "  ";
		}
		std::cout << (*player).getskills().size() + 1 << "." << "返回 ";
		std::cout << std::endl;
		std::cout << "请选择：";
		std::string input;
		std::cin >> input;
		int pos = input[0] - 49;
		while (input.size() > 1 || input[0] - 48 < 1 || input[0] - 48 > (*player).getskills().size() + 1 || (*player).getskills()[pos].getMagicLose() > (*player).getMp())//输入错误
		{
			if(input.size() > 1 || input[0] - 48 < 1 || input[0] - 48 > (*player).getskills().size() + 1 )
			{
				std::cout << "输入错误，请重新选择：";
			}
			else
			{
				std::cout << "当前魔法不足，请重新选择：";
			}
			std::cin >> input;
			pos = input[0] - 49;
			if (input[0] - 48 == (*player).getskills().size() + 1)//返回
			{
				playerRound();
				return -1;
			}
		}
		if (input[0] - 48 == (*player).getskills().size() + 1)//返回
		{
			playerRound();
			return -1;
		}
		std::cout << "你对" << enemy.getName() << "使用了技能--" << (*player).getskills()[pos].getName() << "." << std::endl;
		ms_sleep(1000);
		(*player).adjustMp(-(*player).getskills()[pos].getMagicLose());
		if (enemy.getDefend() > (*player).getskills()[pos].getHarm())
		{
			std::cout << enemy.getName() << "抵挡住了你的攻击。" << std::endl;
			ms_sleep(1000);
		}
		else
		{
			std::cout << "你对" << enemy.getName() << "造成了" << (*player).getskills()[pos].getHarm() - enemy.getDefend() << "点伤害。" << std::endl;
			ms_sleep(1000);
			enemy.adjustHp(enemy.getDefend() - (*player).getskills()[pos].getHarm());
		}
		return -1;
	}
	case '3'://使用物品
	{
		int num01 = 1;
        for (auto i = player->getMedicine().begin(); i != player->getMedicine().end(); i++)
        {
        	std::cout << num01 << "." << i->first->name << "  ";
        	num01++;
        }
		if(num01 == 1)
		{
			std::cout<<"当前没有药品可用！"<<std::endl;
		}
        std::cout << num01 << ".返回" << std::endl;
        std::cout << "请选择：";
        std::string input;
        std::cin >> input;
        while (input.size() > 1 || input[0] - 48 < 1 || input[0] - 48 > num01)//输入错误
        {
        	std::cout << "输入错误，请重新选择:" << std::endl;
        	std::cin >> input;
        }
        if (input[0] - 48 == num01)//返回
        {
        	playerRound();
        	return -1;
        }
        auto i = player->getMedicine().begin();
        int num02 = 1;
        for (i = player->getMedicine().begin(); i != player->getMedicine().end(); i++)
        {
        	if (num02 == input[0] - 48)
           {
        		break;
           }
        	num02++;
        }
        player->use(i->first,1);
        std::cout << "使用" << i->first->name << "成功！" << std::endl;
		player->showHero();
        playerRound();
		return -1;
	}
	case '4'://逃跑,返回0逃跑失败，返回1逃跑成功
	{
		if (enemy.getThreaten() < 3)
		{
			return 0;
		}
		else
		{
			if (rand() % 6 < enemy.getThreaten())
			{
				return 1;
			}
			return 0;
		}
	}
	default:
		return -1;
	}
}

void Battle::enemyRound()//对手攻击或使用技能
{
	while (1)
	{
		if(enemy.getSkillnum()==0)
		{
			throw std::invalid_argument("敌人技能数目为0");
		}
		int num = rand() % enemy.getSkillnum();
		if (enemy.getSkill(num).getMagicLose() > enemy.getMp())
			continue;
		enemy.adjustMp(-enemy.getSkill(num).getMagicLose());
		int harm = enemy.getSkill(num).getHarm();

		std::cout << enemy.getName() << "使用了" << enemy.getSkill(num).getName() << "." << std::endl;
		ms_sleep(1000);
		if (harm - (*player).getDefend() > 0)
		{
			std::cout << enemy.getName() << "对你造成了" << harm - (*player).getDefend() << "点伤害。" << std::endl << std::endl;
			ms_sleep(1000);
			(*player).adjustHp((*player).getDefend() - harm);
		}
		else
		{
			std::cout << "你成功抵御了" << enemy.getName() << "攻击。" << std::endl << std::endl;
			ms_sleep(1000);
		}
		break;
	}
	ms_sleep(1000);

	eraseScreen();

}
bool Battle::ifEnd()//战斗是否结束
{
	if (enemy.getHp() <= 0 || (*player).getHp() <= 0)
	{
		return true;
	}
	return false;
}
void Battle::battleEnd()
{
	std::cout << enemy.getName() << "掉落了" << enemy.getGold() << "枚金币。" << std::endl;
	std::cout << "你获得了" << enemy.getExp() << "点经验值。" << std::endl;
	player->addExp(enemy.getExp());
	player->adjustGold(enemy.getGold());
	ms_sleep(2000);
	eraseScreen();
}


// see fight1 instead
// void fight()
// {
// 	ms_sleep(500);
// 	std::cout << "战斗开始！" << std::endl;
// 	ms_sleep(1000);
// 	while (!ifEnd())
// 	{
// 		showRound();
// 		int cur = playerRound();//返回值判断是否逃跑，逃跑是否成功
// 		if (cur == 0)//返回值为0代表逃跑成功
// 		{
// 			ms_sleep(1000);
// 			std::cout << "你逃跑了";
// 			return;
// 		}
// 		else if (cur == 1)//返回1代表逃跑失败 返回-1代表没有逃跑
// 		{
// 			ms_sleep(1000);
// 			std::cout << "逃跑失败！" << std::endl;
// 		}

// 		if (ifEnd()) break;
// 		enemyRound();
// 		round++;
// 	}
// 	if (enemy.getHp() <= 0)
// 	{
// 		std::cout << "你成功打败了对手。" << std::endl;
// 		ms_sleep(2000);
// 	}
// 	else if (((*player).getHp() <= 0))
// 	{
// 		std::cout << "很遗憾，你的旅程到此为止。" << std::endl;
// 	}
// 	battleEnd();//结算
// }

void fightTunnel(Hero* hero)
{
	Enemy e1("小刺球","这种怪物可能全身布满尖锐的小刺，但攻击力不高。",30,30,0,0,10,5,1,5,1);
	Enemy e2("腐叶虫","生活在腐叶堆中的小虫子，外观可能有些恶心，但威胁不大。",30,30,0,0,10,5,1,5,1);
	Enemy e3("咕噜怪","是个会发出咕噜声的小型怪物，攻击力较弱。",30,30,10,0,0,5,1,5,1);
	Enemy e4("蜗牛壳兵","背着蜗牛壳的小型士兵，移动缓慢，攻击力也很有限。",30,30,0,0,10,5,1,5,1);
	Enemy e5("迷途史莱姆","一种透明的、像果冻一样的生物，有时会迷路攻击其他生物。",30,30,0,0,10,5,1,5,1);

	Skill s1("冲撞", "大凶兔气势汹汹的一击，威力不可小觑。", 20, 0);
	Skill s2("噬咬", "大凶兔气势汹汹的一击，威力不可小觑。", 20, 0);
	Skill s3("爪击", "大凶兔气势汹汹的一击，威力不可小觑。", 20, 0);
	Skill s4("爪击", "大凶兔气势汹汹的一击，威力不可小觑。", 20, 0);
	Skill s5("喷射", "大凶兔气势汹汹的一击，威力不可小觑。", 20, 0);

	Skill S1[1] = { s1 };
	Skill S2[1] = { s2 };
	Skill S3[1] = { s3 };
	Skill S4[1] = { s4 };
	Skill S5[1] = { s5 };
	e1.setSkill(S1, 1);
	e2.setSkill(S2, 1);
	e3.setSkill(S3, 1);
	e4.setSkill(S4, 1);
	e5.setSkill(S5, 1);
	Enemy enem[5]={e1,e2,e3,e4,e5};
	int num = rand() % 5;
	//std::cout<<enem[num].getName()<<"："<<enem[num].getIntroduce()<<" "<<"威胁指数："<<"*"<<std::endl;
	Battle battle(hero,enem[num]);
	// if(ifFight()==-1)
	// {
	// 	ms_sleep(500);
	// 	eraseScreen();
	// 	Battle battle(hero,enem[num]);
	// }
}
void fightCellar(Hero* hero)
{
    Enemy e1("毒蛛","一种有毒的蜘蛛类怪物。",80,80,20,20,30,10,2,10,5);
	Enemy e2("钝刃骷髅","一种由骨骼构成的亡灵类怪物。",80,80,20,20,30,10,2,10,5);
	Enemy e3("残影妖","一种妖异邪恶的怪物。",80,80,20,20,30,10,2,10,5);
	Enemy e4("幼岩魔","一种由岩石构成或生活在岩石中的魔物。",80,80,20,20,30,10,2,10,5);
	Enemy e5("嗜血蝙蝠","一种凶恶的蝙蝠。",80,80,20,20,30,10,2,10,5);

	Skill s11("毒丝缠绕", "毒蛛快速从腹部喷出粘性极强的毒丝进行攻击。", 40, 10);
	Skill s12("突袭", "毒蛛快速从腹部喷出粘性极强的毒丝进行攻击。", 30, 0);
	
	Skill s21("骨盾冲击", "举起由骨骼构成的巨大盾牌，向目标发起冲锋。", 40, 10);
	Skill s22("横扫", "蓄力向四周挥舞巨剑。", 30, 0);

	Skill s31("幻影", "分裂成多个幻影集中进行打击。", 40, 10);
	Skill s32("侵蚀", "释放出黑暗能量，对目标造成暗影伤害。", 30, 0);

	Skill s41("岩崩", "从地面召唤出坚硬的岩石砸向目标。", 40, 10);
	Skill s42("地裂", "用力锤击地面，引发周围地面震动造成伤害。", 30, 0);

	Skill s51("血之诅咒","对目标施加血之诅咒，使其受到伤害。", 40, 10);
	Skill s52("俯冲", "以极快的速度俯冲向目标，用锋利的爪子发动攻击。", 30, 0);

	Skill S1[2] = { s11,s12 };
	Skill S2[2] = { s21,s22 };
	Skill S3[2] = { s31,s32 };
	Skill S4[2] = { s41,s42 };
	Skill S5[2] = { s51,s52 };

	e1.setSkill(S1, 2);
	e2.setSkill(S2, 2);
	e3.setSkill(S3, 2);
	e4.setSkill(S4, 2);
	e5.setSkill(S5, 2);
	Enemy enem[5]={e1,e2,e3,e4,e5};
	int num = rand() % 5;
	//std::cout<<enem[num].getName()<<"："<<enem[num].getIntroduce()<<" "<<"威胁指数："<<"*"<<std::endl;
	Battle battle(hero,enem[num]);
	// if(ifFight()==-1)
	// {
	// 	ms_sleep(500);
	// 	eraseScreen();
	// 	Battle battle(hero,enem[num]);
	// }
}
void fightDenOfDisaster(Hero* hero)
{    
	Enemy e1("影魔","恐怖魔物，潜行于黑暗之中，伺机发动致命一击，遇到阳光会被灼伤。",180,180,100,100,60,30,3,50,30);
	Enemy e2("长角恶鬼","地狱族的勇猛战士，长角狰狞，有强大的肉搏能力。",180,180,100,100,60,30,3,50,30);
	Enemy e3("骷髅勇士","不死军团的精锐，骨骼非常坚硬。",180,180,100,100,60,30,3,50,30);
	Enemy e4("僵尸","行动迟缓但攻击性极强的不死生物。",180,180,100,100,60,30,3,50,30);
	Enemy e5("幽灵","无形之态的恐怖存在。",180,180,100,100,60,30,3,50,30);

	Skill s11("咆哮", "发出尖叫，对周围所有敌人造成音波攻击。", 100, 40);
	Skill s12("潜袭", "悄无声息地接近目标，并发动突然袭击。", 60, 0);

	Skill s21("地狱之火", "从口中喷出熊熊地狱之火，对敌人造成火焰伤害。", 100, 40);
	Skill s22("突刺", "快速冲向目标利用长角攻击。", 60, 0);

	Skill s31("骨盾冲击", "举起由骨骼构成的巨大盾牌，向目标发起冲锋。", 100, 40);
	Skill s32("剧烈冲撞", "利用庞大的身躯猛然发动冲撞。", 60, 0);

	Skill s41("腐烂之触", "通过腐烂的身体接触敌人，传播致命的毒素。", 100, 40);
	Skill s42("狂暴冲锋", "爆发出惊人的力量，向前方冲锋并攻击。", 60, 0);

	Skill s51("灵魂吸噬","对目标发动吸噬，吸取灵魂，造成伤害。", 100, 40);
	Skill s52("无形穿梭", "以无形之态穿梭于战场之间，对敌人进行偷袭。", 60, 0);

	Skill S1[2] = { s11,s12 };
	Skill S2[2] = { s21,s22 };
	Skill S3[2] = { s31,s32 };
	Skill S4[2] = { s41,s42 };
	Skill S5[2] = { s51,s52 };

	e1.setSkill(S1, 2);
	e2.setSkill(S2, 2);
	e3.setSkill(S3, 2);
	e4.setSkill(S4, 2);
	e5.setSkill(S5, 2);
	Enemy enem[5]={e1,e2,e3,e4,e5};
	int num = rand() % 5;
	//std::cout<<enem[num].getName()<<"："<<enem[num].getIntroduce()<<" "<<"威胁指数："<<"*"<<std::endl;
	Battle battle(hero,enem[num]);
	// if(ifFight()==-1)
	// {
	// 	ms_sleep(500);
	// 	eraseScreen();
	// 	Battle battle(hero,enem[num]);
	// }
}
void fightGrottoes(Hero* hero)
{
	Enemy e1("狼人","非常狂暴的一种兽人，行动敏捷，战斗经验丰富。",360,360,100,100,100,50,4,200,40);
	Enemy e2("食人魔","体型庞大，丑陋贪婪，以掠夺和偷窃为生，偏好食用人类等种族。",360,360,100,100,100,50,4,200,40);
	Enemy e3("吸血鬼","以人类血液为生的不死生物，拥有超自然力量。",360,360,100,100,100,50,4,200,40);

	Skill s11("狂暴爪击", "利用锋利的手爪攻击目标。", 130, 40);
	Skill s12("野性突袭", "悄无声息地接近目标，并发动突然袭击。", 100, 0);

	Skill s21("巨力投掷", "抓起身边的一个大型物体向目标砸去。", 130, 40);
	Skill s22("贪婪噬咬", "张开巨口吞噬敌人。", 100, 0);

	Skill s31("血之盛宴", "瞬间移动到其身边并吸取其血液。", 130, 40);
	Skill s32("暗影遁击", "化为一团黑雾，接近并攻击敌人。", 100, 0);


	Skill S1[2] = { s11,s12 };
	Skill S2[2] = { s21,s22 };
	Skill S3[2] = { s31,s32 };

	e1.setSkill(S1, 2);
	e2.setSkill(S2, 2);
	e3.setSkill(S3, 2);
	Enemy enem[3]={e1,e2,e3};
	int num = rand() % 3;
	//std::cout<<enem[num].getName()<<"："<<enem[num].getIntroduce()<<" "<<"威胁指数："<<"*"<<std::endl;
	Battle battle(hero,enem[num]);
	// if(ifFight()==-1)
	// {
	// 	ms_sleep(500);
	// 	eraseScreen();
	// 	Battle battle(hero,enem[num]);
	// }
	  
}
void fightDungeon(Hero* hero)
{
	Enemy e1("地狱猎犬","拥有三个头颅的邪恶生物，是地狱的守卫。",600,600,100,100,150,60,5,500,100);
	Enemy e2("独眼巨人","额头上长有一只独眼。强壮、固执且擅长制造和使用各种工具和武器。",600,600,100,100,150,60,5,500,100);
	Enemy e3("比蒙巨兽","体型如山，力大无穷，传说中的存在，令人畏惧。",600,600,100,100,150,60,5,500,100);

	Skill s11("狂暴爪击", "利用锋利的手爪攻击目标。", 200, 40);
	Skill s12("野性突袭", "悄无声息地接近目标，并发动突然袭击。", 150, 0);

	Skill s21("巨力投掷", "抓起身边的一个大型物体向目标砸去。", 200, 40);
	Skill s22("贪婪噬咬", "张开巨口吞噬敌人。", 150, 0);

	Skill s31("血之盛宴", "瞬间移动到其身边并吸取其血液。", 200, 40);
	Skill s32("暗影遁击", "化为一团黑雾，接近并攻击敌人。", 150, 0);


	Skill S1[2] = { s11,s12 };
	Skill S2[2] = { s21,s22 };
	Skill S3[2] = { s31,s32 };

	e1.setSkill(S1, 2);
	e2.setSkill(S2, 2);
	e3.setSkill(S3, 2);
	Enemy enem[3]={e1,e2,e3};
	int num = rand() % 3;
	//std::cout<<enem[num].getName()<<"："<<enem[num].getIntroduce()<<" "<<"威胁指数："<<"*"<<std::endl;
	Battle battle(hero,enem[num]);
	// if(ifFight()==-1)
	// {
	// 	ms_sleep(500);
	// 	eraseScreen();
	// 	Battle battle(hero,enem[num]);
	// }
}
void fightGhostdom(Hero* hero)
{
	Enemy e1("鬼眼-阿比斯","地下三巨头之一，本体是一只巨大的眼球。",16000,16000,5000,5000,3000,1000,6,5000,1000);

	Skill s1("幽冥凝视", "阿比斯睁开其深邃的鬼眼，对前方扇形区域内的所有敌人释放一股不可见的幽冥能量。", 4000, 200);
	Skill s2("灵魂窃取", "阿比斯锁定一个敌人，用其鬼眼直接窥视其灵魂深处，造成不可逆转的伤害。", 4000, 200);
	Skill s3("终焉之眼", "阿比斯的终极技能，他集中全身的力量于巨眼之中，释放出毁灭性的能量波。", 5000, 2000);
	Skill s4("阿比冲撞", "利用巨大的身躯压制敌人。", 5000, 0);

	Skill S[4]={s1,s2,s3,s4};
	e1.setSkill(S, 2);
	Battle battle(hero,e1); 
}
void fightSweatPore(Hero* hero)
{
	Enemy e1("冥王","地下三巨头之一，即使本身处于负伤状态在地下也难以遇到对手。",15000,15000,4000,4000,2500,1100,6,5000,1000);

	Skill s1("生死轮回", "冥王挥动权杖，召唤出冥界的轮回之力，选定一名敌人作为目标造成大量伤害。", 3000, 200);
	Skill s2("幽冥波", "利用法杖对敌人使用能量波进行攻击。", 2500, 0);
	Skill s3("幽冥审判", "冥王的终极技能，凝聚全身的幽冥之力，对全场所有敌人发动一次致命的审判。", 4000, 1000);
	Skill s4("冥界之门", "召唤冥界之门吞噬对手。", 3000, 200);

	Skill S[4]={s1,s2,s3,s4};
	e1.setSkill(S, 2);
	Battle battle(hero,e1);
}
void fightDarkRom(Hero* hero)
{
	Enemy e1("地灵","地下空间的掌控者，在很长一段时间内没有得到充足的能量，现在的状态早已不比全胜时期。",20000,20000,8000,8000,5000,3000,6,10000,10000);

	Skill s1("灵魂穿梭", "瞬间移动至敌方身前，对敌人造成精神伤害。", 6000, 1000);
	Skill s2("精神冲击", "释放出一股强大的精神能量波，对前方直线上的所有敌人造成高额的精神伤害。", 5000, 0);
	Skill s3("幽影束缚", "从虚空中召唤出数条幽影锁链，束缚住敌人并造成伤害。", 6000, 1000);
	Skill s4("灵界领域", "张开一个特殊领域，整个地下空间任其调控。", 7000, 4000);

	Skill S[4]={s1,s2,s3,s4};
	e1.setSkill(S, 2);
	Battle battle(hero,e1);
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
  table.SelectRow(0).Border(ftxui::DOUBLE);
  table.SelectRow(0).Border(ftxui::DOUBLE);
  return table.Render();
}

const char* const defVal = "                                                 ";
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



void fight1(Hero& hero,Enemy& enemy)
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
        if(end == false)
        {
            enemyAttack(hero,enemy);
			if (hero.getHp() <= 0)
            {
				str = defVal;
				str1 = defVal;
				str2 = defVal;
				str3 = defVal;
				closeFunc();                
				std::cout << std::endl <<"战斗失败,游戏结束";
				ms_sleep(1000);
				throw FailCombat();
            }
        }
        else
        {
            closeFunc();
            if (hero.getHp() <= 0)
            {
				str = defVal;
				str1 = defVal;
				str2 = defVal;
				str3 = defVal;
				closeFunc();                
				std::cout << std::endl <<"战斗失败,游戏结束";
				ms_sleep(1000);
				throw FailCombat();
				
            }
            else if(enemy.getHp() <= 0 )
            {
				str = defVal;
				str1 = defVal;
				str2 = defVal;
				str3 = defVal;
				closeFunc();                
				std::cout << std::endl<< "战斗成功";
				ms_sleep(1000);
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
				str = defVal;
				str1 = defVal;
				str2 = defVal;
				str3 = defVal;
                closeFunc();
                std::cout << "逃跑成功";
				ms_sleep(1000);
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
            medicine.push_back(Button(i.first->name ,[&,i]{
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
    auto buttons = ftxui::Container::Vertical({ 
      ftxui::Container::Horizontal({btn0}, &row) | flex,
      ftxui::Container::Horizontal(skill, &row) | flex,
      ftxui::Container::Horizontal(medicine, &row) | flex,      
      ftxui::Container::Horizontal({btn1}, &row)  | flex,
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
					text(defVal),
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
