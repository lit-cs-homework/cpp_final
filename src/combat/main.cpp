
#include "../../include/combat.h"

using namespace std;

#ifdef _WIN32
# include<windows.h>
#else
//#include <unistd.h>
#endif

static
void ms_sleep(int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	struct timespec tp = {
		ms / 1000,    // second
		ms % 1000000  // ns
	};
	nanosleep(tp, NULL);
#endif
}

Skill::Skill() {}
Skill::Skill(string name, string introduce, int harm, int magicLose) :name(name), introduce(introduce), harm(harm), magicLose(magicLose) {}
Skill::~Skill() {}
void Skill::showSkill()
{
	cout << "--" << name << "--" << endl;
	cout << introduce << endl;
	cout << "伤害: " << harm << "  ";
	cout << "耗蓝: " << magicLose << endl;
}
string Skill::getName()
{
	return name;
}
string Skill::getIntroduce()
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



Hero::Hero()
{
	setName();
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
	cout << "请设置您的昵称： ";
	string tmpName;
	cin >> tmpName;
	name = tmpName;
	system("cls");
}
void Hero::showHero()
{
	cout << "--" << name << "--" << endl;
	cout << "等级： " << level << "  ";
	cout << "经验： " << exp << "/" << expMax[level - 1] << "  ";
	cout << "hp: " << hp << "/" << hpMax << "  ";
	cout << "mp: " << mp << "/" << mpMax << "  ";
	cout << "攻击: " << attack << "  ";
	cout << "防御: " << defend << endl;
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
		cout << "恭喜你升到了 " << level << "级！ " << endl;
		hp += 20;
		mp += 10;
		attack += 5;
		defend += 3;
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
void Hero::setSkill(Skill skill)
{
	skills.push_back(skill);
}
vector<Skill> Hero::getskills()
{
	return skills;
}



Enemy::Enemy() {}
Enemy::Enemy(string name, string introduce, int hp, int hpMax, int mp, int mpMax, int attack, int defend, int threaten, int exp, int gold) : name(name), introduce(introduce), hp(hp), hpMax(hpMax), mp(mp), mpMax(mpMax), attack(attack), defend(defend), threaten(threaten), exp(exp), gold(gold)
{
	;
}
Enemy::~Enemy() {}
void Enemy::showEnemy()
{
	cout << "--" << name << "--" << endl;
	//cout << introduce << endl;
	cout << "hp: " << hp << "/" << hpMax << "  ";
	cout << "mp: " << mp << "/" << mpMax << "  ";
	cout << "攻击: " << attack << "  ";
	cout << "防御: " << defend << "  ";
	cout << "威胁指数：";
	for (int i = 1; i <= threaten; i++) cout << "*";
	cout << endl;
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
string Enemy::getName()
{
	return name;
}
int Enemy::getHp()
{
	return hp;
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
	fight();
}
Battle::~Battle() {}
void Battle::showRound()//回合演示
{
	cout << "----回合 " << round << "----" << endl;
	ms_sleep(500);
	(*player).showHero();
	ms_sleep(1000);
	enemy.showEnemy();
	ms_sleep(1000);
}

int Battle::playerRound()
{
	cout << "请选择： " << "1.攻击  2.使用技能  3.使用物品   4.尝试逃跑 " << endl;
	string input;
	cin >> input;
	while (input.size() > 1 || input[0] - 48 < 1 || input[0] - 48 > 4)//输入错误
	{
		cout << "输入错误，请重新选择: ";
		cin >> input;
	}
	switch (input[0])
	{
	case '1'://攻击
	{
		cout << "你对 " << enemy.getName() << "进行了攻击。 " << endl;
		ms_sleep(1000);
		if (enemy.getDefend() > (*player).getAttack())
		{
			cout << enemy.getName() << "抵挡住了你的攻击。 " << endl;
			ms_sleep(1000);
		}
		else
		{
			cout << "你对 " << enemy.getName() << "造成了 " << (*player).getAttack() - enemy.getDefend() << "点伤害。 " << endl;
			ms_sleep(1000);
			enemy.adjustHp(enemy.getDefend() - (*player).getAttack());
		}
		return -1;
	}
	case'2'://使用技能
	{
		for (int i = 1; i <= (*player).getskills().size(); i++)
		{
			cout << i << "." << (*player).getskills()[i - 1].getName() << "  ";
		}
		cout << (*player).getskills().size() + 1 << "." << "返回 ";
		cout << endl;
		cout << "请选择： ";
		string input;
		cin >> input;
		while (input.size() > 1 || input[0] - 48 < 1 || input[0] - 48 > (*player).getskills().size() + 1)//输入错误
		{
			cout << "输入错误，请重新选择: ";
			cin >> input;
		}
		if (input[0] - 48 == (*player).getskills().size() + 1)//返回
		{
			playerRound();
			return -1;
		}
		int pos = input[0] - 49;
		while ((*player).getskills()[pos].getMagicLose() > (*player).getMp())//魔法不足
		{
			cout << "当前魔法不足，请重新选择: ";
			cin >> input;
		}
		cout << "你对 " << enemy.getName() << "使用了技能-- " << (*player).getskills()[pos].getName() << "。" << endl;
		ms_sleep(1000);
		(*player).adjustMp(-(*player).getskills()[pos].getMagicLose());
		if (enemy.getDefend() > (*player).getskills()[pos].getHarm())
		{
			cout << enemy.getName() << "抵挡住了你的攻击。 " << endl;
			ms_sleep(1000);
		}
		else
		{
			cout << "你对 " << enemy.getName() << "造成了 " << (*player).getskills()[pos].getHarm() - enemy.getDefend() << "点伤害。 " << endl;
			ms_sleep(1000);
			enemy.adjustHp(enemy.getDefend() - (*player).getskills()[pos].getHarm());
		}
		return -1;
	}
	case'3'://使用物品
	{
		//int num01 = 1;
        //for (auto i = player->getBag().getMedicinebag().begin(); i != player->getBag().getMedicinebag().end(); i++)
        //{
        //	cout << num01 << "." << i->first.name << "  ";
        //	num01++;
        //}
        //cout << num01 << ".返回" << endl;
        //cout << "请选择：";
        //string input;
        //cin >> input;
        //while (input.size() > 1 || input[0] - 48 < 1 || input[0] - 48 > num01)//输入错误
        //{
        //	cout << "输入错误，请重新选择:";
        //	cin >> input;
        //}
        //if (input[0] - 48 == num01)//返回
        //{
        //	playerRound();
        //	return -1;
        //}
        //auto i = player->getBag().getMedicinebag().begin();
        //int num02 = 1;
        //for (i = player->getBag().getMedicinebag().begin(); i != player->getBag().getMedicinebag().end(); i++)
        //{
        //	if (num02 == input[0] - 48)
        //{
        //		break;
        //}
        //	num02++;
        //}
        //player->getBag().use(i->first, 1);
        //cout << "使用" << i->first.name << "成功！" << endl;
        //playerRound();
		return -1;
	}
	case'4'://逃跑,返回0逃跑失败，返回1逃跑成功
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
		int num = rand() % enemy.getSkillnum();
		if (enemy.getSkill(num).getMagicLose() >= enemy.getMp())
			continue;
		enemy.adjustMp(-enemy.getSkill(num).getMagicLose());
		int harm = enemy.getSkill(num).getHarm();

		cout << enemy.getName() << "使用了 " << enemy.getSkill(num).getName() << "。" << endl;
		ms_sleep(1000);
		if (harm - (*player).getDefend() > 0)
		{
			cout << enemy.getName() << "对你造成了 " << harm - (*player).getDefend() << "点伤害。 " << endl << endl;
			ms_sleep(1000);
			(*player).adjustHp((*player).getDefend() - harm);
		}
		else
		{
			cout << "你成功抵御了 " << "enemy.getName()" << "攻击。 " << endl << endl;
			ms_sleep(1000);
		}
		break;
	}
	ms_sleep(1000);

#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif

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
	cout << enemy.getName() << "掉落了" << enemy.getGold() << "枚金币。" << endl;
	cout << "你获得了" << enemy.getExp() << "点经验值。" << endl;
	player->addExp(enemy.getExp());
	player->adjustGold(enemy.getGold());

}
void Battle::fight()
{
	ms_sleep(500);
	cout << "战斗开始！ " << endl;
	ms_sleep(1000);
	while (!ifEnd())
	{
		showRound();
		int cur = playerRound();//返回值判断是否逃跑，逃跑是否成功
		if (cur == 0)//返回值为0代表逃跑成功
		{
			ms_sleep(1000);
			cout << "你逃跑了 ";
			return;
		}
		else if (cur == 1)//返回1代表逃跑失败 返回-1代表没有逃跑
		{
			ms_sleep(1000);
			cout << "逃跑失败！ " << endl;
		}

		if (ifEnd()) break;
		enemyRound();
		round++;
	}
	if (enemy.getHp() <= 0)
	{
		cout << "你成功打败了对手。 " << endl;
	}
	else if (((*player).getHp() <= 0))
	{
		cout << "很遗憾，你的旅程到此为止。 " << endl;
	}
	battleEnd();//结算
}

