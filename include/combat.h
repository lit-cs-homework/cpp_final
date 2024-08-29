#pragma once
#include<iostream>
#include<algorithm>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<vector>
//#include"../../include/equip.h"
using namespace std;
class Skill
{
public:
	Skill();
	Skill(string name, string introduce, int harm, int magicLose);
	~Skill();
	void showSkill();
	string getName();
	string getIntroduce();
	int getHarm();
	int getMagicLose();
private:
	string name;//名称
	string introduce;//介绍
	int harm;//伤害
	int magicLose;//耗蓝
};


class Hero
{
public:
	Hero();
	~Hero();
	void setName();
	void showHero();
	void addHp(int num);//增加生命上限
	void adjustHp(int num);//增加或减少生命值
	void addMp(int num);//增加魔法上限
	void adjustMp(int num);//增加或减少魔法值
	void adjustAttack(int num);//增加或减少攻击
	void adjustDefend(int num);//增加或减少防御
	void addExp(int num);//增加或减少经验
	void adjustGold(int num);//增加或减少金币
	int getHp();
	int getMp();
	int getAttack();
	int getDefend();
	int getExp();
	int getGold();
	int getLevel();
	//Bag& getBag();
	void setSkill(Skill skill);
	vector<Skill> getskills();
private:
	string name;
	int hp;//血量
	int hpMax;
	int mp;//蓝量
	int mpMax;
	int attack;
	int defend;
	int exp;
	int expMax[10] = { 10,50,150,500,1000,2000,4000,8000,15000,30000 };
	int level;
	int gold;
	vector<Skill> skills;
	int skillNumber;//技能最大数目；
};

class Enemy
{
public:
	Enemy();
	Enemy(string name, string introduce, int hp, int hpMax, int mp, int mpMax, int attack, int defend, int threaten, int exp, int gold);
	~Enemy();
	void showEnemy();
	void adjustHp(int num);//增加或减少生命值
	void adjustMp(int num);//增加或减少魔法值
	void adjustAttack(int num);//增加或减少攻击
	void adjustDefend(int num);//增加或减少防御
	string getName();
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
	string name;
	string introduce;
	int hp;//血量
	int hpMax;
	int mp;//蓝量
	int mpMax;
	int attack;
	int defend;
	vector<Skill> skills;
	int exp;//死亡掉落经验
	int gold;//死亡掉落金钱
	//vector<Stuff> stuffs;//死亡掉落物品
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
