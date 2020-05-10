/*
 * Unit.hpp
 */

#ifndef UNIT_HPP
#define UNIT_HPP

#include <stdlib.h>

#include "../includes/Player.hpp"
#include "../includes/Tile.hpp"
#include "../src/Exceptions.cpp"

class Tile;
class Player;

class Unit {

public:
	enum Type {
		Infantry, Artillery, Tank
	};

	Unit(int id, Player *player);
	Unit(int id, Player *player, Type type);
	Unit(int id, Player *player, Type type,
			 int hp, int hpMax,
			 int mp, int mpMax,
			 int ratk, int atkcost,
			 int atk, int def);
	~Unit();

	int getId() const { return m_id; }
	void setId(int id) { m_id = id; }
	Type getType() const { return m_type; }
	void setType(Type type) { m_type = type; }
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
	void setTile(Tile *tile) { m_tile = tile; }
	int getRatk() const { return m_ratk; }
	void setRatk(int ratk) { m_ratk = ratk; }

	bool isDead() const { return m_hp <= 0; }
	bool canMoveOn(Tile *t) const;
	bool canHit(Unit *u) const { return distanceFrom(u->getTile()) <= m_ratk; }
	bool canHit(Tile *t) const { return distanceFrom(t) <= m_ratk; }
	bool canHit(int x, int y) const { return distanceFrom(x, y) <= m_ratk; }

	void takeDamage(int v);
	int distanceFrom(Tile *t) const;
	int distanceFrom(int x, int y) const;
	void die();

private:
	int m_id;
	Type m_type;
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

#endif /* UNIT_HPP */
