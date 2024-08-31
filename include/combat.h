#pragma once

#include <algorithm>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <memory>
#include "./equip.h"
//#include "equip.h"

class Enemy
{
public:
	Enemy();
	Enemy(std::string name, std::string introduce, int hp, int hpMax, int mp, int mpMax, int attack, int defend, int threaten, int exp, int gold);
	~Enemy();
	void showEnemy();
	void adjustHp(int num);//增加或减少生命值
	void adjustMp(int num);//增加或减少魔法值
	void adjustAttack(int num);//增加或减少攻击
	void adjustDefend(int num);//增加或减少防御
	std::string getName();
	int getHp();
	int getMp();
	int getAttack();
	int getDefend();
	int getSkillnum();
	int getThreaten();
	int getExp();
	int getGold();
	Skill getSkill(int pos);
	void setSkill(Skill skill[], int num);//设置技能
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

	void fight();//战斗开始
	void showRound();//回合演示

	int playerRound();//玩家行动

	void enemyRound();//对手行动

	bool ifEnd();//战斗是否结束

	void battleEnd();//结算
private:
	Hero* player;
	Enemy enemy;
	int round;//回合
};

void Fight(Hero* hero);