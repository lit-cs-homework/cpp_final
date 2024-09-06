#pragma once

#include <algorithm>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "./equip.h"
//#include "equip.h"
#include <memory>  // for shared_ptr, __shared_ptr_access
#include <string>  // for operator+, to_string

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, gauge, text, Element, operator|, vbox, border

int ifFight();

class Enemy
{
public:
	Enemy();
	Enemy(std::string name, std::string introduce, int hp, int hpMax, int mp, int mpMax, int attack, int defend, int threaten, int exp, int gold);
	~Enemy();
	void showEnemy();
	//增加或减少生命值
	void adjustHp(int num);
	//增加或减少魔法值
	void adjustMp(int num);
	//增加或减少攻击
	void adjustAttack(int num);
	//增加或减少防御
	void adjustDefend(int num);
	std::string getName();
	std::string getIntroduce();
	int getHp();
	int getHpMax();
	int getMp();
	int getAttack();
	int getDefend();
	int getSkillnum();
	int getThreaten();
	int getExp();
	int getGold();
	Skill getSkill(int pos);
	//设置技能
	void setSkill(Skill skill[], int num);
private:
	std::string name;
	std::string introduce;
	int hp;//血量
	int hpMax;
	int mp;//蓝量
	int mpMax;
	int attack;
	int defend;
	std::vector<Skill> skills;
	int exp;//死亡掉落经验
	int gold;//死亡掉落金钱
	//std::vector<Stuff> stuffs;//死亡掉落物品
	int threaten;//威胁指数，影响逃跑概率
};

class Battle
{
public:
	Battle(Hero* hero, Enemy enemy);//构造
	~Battle();//析构
    //战斗开始
	void fight();
	//回合演示
	void showRound();

	//玩家行动
	int playerRound();

	///对手行动
	///@throw invalid_argument when no skill is set
	void enemyRound();
	//战斗是否结束
	bool ifEnd();
	//结算
	void battleEnd();
private:
	Hero* player;
	Enemy enemy;
	int round;//回合
};

void fightTunnel(Hero* hero);
void fightCellar(Hero* hero);
void fightDenOfDisaster(Hero* hero);
void fightGrottoes(Hero* hero);
void fightGrottoes(Hero* hero);
void fightDungeon(Hero* hero);
void fightGhostdom(Hero* hero);
void fightSweatPore(Hero* hero);
void fightDarkRom(Hero* hero);
void fight1(Hero& hero,Enemy& enemy);