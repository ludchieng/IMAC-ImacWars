/*
 * Unit.h
 */

#ifndef UNIT_H_
#define UNIT_H_

#include <sstream>
#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

class Unit {
	int m_id;
	int m_player;
	int m_hp;
	int m_hpMax;
	int m_mp;
	int m_mpMax;
	int m_ratk;
	int m_atk;
	int m_def;

public:
	Unit(int id, int player);
	Unit(int id, int player, int hp, int hpMax, int mp, int mpMax, int ratk, int atk, int def);

	int getId() const;
	void setId(int id);
	int getAtk() const;
	void setAtk(int atk);
	int getDef() const;
	void setDef(int def);
	int getHp() const;
	void setHp(int hp);
	int getHpMax() const;
	void setHpMax(int hpMax);
	int getMp() const;
	void setMp(int mp);
	int getMpMax() const;
	void setMpMax(int mpMax);
	int getPlayer() const;
	void setPlayer(int player);
	int getRatk() const;
	void setRatk(int ratk);
	std::string toString();

	bool isVisibleBy(const Unit *&u);
	bool isDead();

	void move();
	void takeDamage(int v);
	void die();

	void attack(Unit *&target);
};


#endif /* UNIT_H_ */
