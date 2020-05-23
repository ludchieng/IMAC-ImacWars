/*
 * Unit.hpp
 */

#ifndef UNIT_HPP
#define UNIT_HPP

#include <stdlib.h>
#include <stdio.h>

#include "../includes/Player.hpp"
#include "../includes/Tile.hpp"
#include "../src/Exceptions.cpp"

class Tile;
class Player;

class Unit {

public:
	Unit(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def);
	virtual ~Unit();

	int getAtk() const { return m_atk; }
	void setAtk(int atk) { m_atk = atk; }
	int getAtkCost() const { return m_atkcost; }
	void setAtkCost(int atkcost) { m_atkcost = atkcost; }
	int getDef() const { return m_def; }
	void setDef(int def) { m_def = def; }
	int getHp() const { return m_hp; }
	void setHp(int hp) { m_hp = hp; }
	int getHpMax() const { return m_hpMax; }
	void setHpMax(int hpMax) { m_hpMax = hpMax; }
	int getMp() const { return m_mp; }
	void setMp(int mp) { m_mp = mp; }
	int getMpMax() const { return m_mpMax; }
	void setMpMax(int mpMax) { m_mpMax = mpMax; }
	Player *getPlayer() const { return m_player; }
	void setPlayer(Player *player) { m_player = player; }
	Tile *getTile() const { return m_tile; }
	void setTile(Tile *tile);
	int getRatk() const { return m_ratk; }
	void setRatk(int ratk) { m_ratk = ratk; }

	int distanceDirectFrom(Tile *t) const;
	int distanceDirectFrom(int x, int y) const;

	bool isDead() const { return m_hp <= 0; }
	bool canHit(Unit *u) const { return distanceDirectFrom(u->getTile()) <= m_ratk; }
	bool canHit(Tile *t) const { return distanceDirectFrom(t) <= m_ratk; }
	bool canHit(int x, int y) const { return distanceDirectFrom(x, y) <= m_ratk; }
	bool canAttack(Unit *u) const { return canHit(u) && m_mp >= m_atkcost; }
	bool canAttack(Tile *t) const { return canHit(t) && m_mp >= m_atkcost; }
	bool canAttack(int x, int y) const { return canHit(x, y) && m_mp >= m_atkcost; }

	void takeDamage(int v);
	void die();

	static bool canStandOn(Tile* t);
	static bool canStandOn(Land::Type lt);
	static Land::Type getAllowedLandTypes();

protected:
	Player *m_player;
	Tile *m_tile;
	int m_hp;
	int m_hpMax;
	int m_mp;
	int m_mpMax;
	int m_ratk;
	int m_atkcost;
	int m_atk;
	int m_def;
};

#include "../includes/Duck.hpp"
#include "../includes/Bee.hpp"
#include "../includes/Rhino.hpp"

#endif /* UNIT_HPP */
