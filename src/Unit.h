/*
 * Unit.h
 */

#ifndef SRC_UNIT_H_
#define SRC_UNIT_H_

#include <stdlib.h>
#include "exceptions.cpp"
#include "Player.h"
#include "Tile.h"

class Tile;
class Player;

class Unit
{

public:
	enum Type
	{
		Infantry,
		Artillery,
		Tank
	};

	Unit(int id, Player *player);
	Unit(int id, Player *player, Type type);
	Unit(int id, Player *player, Type type,
			 int hp, int hpMax,
			 int mp, int mpMax,
			 int ratk, int atkcost,
			 int atk, int def);

	int getId() const;
	void setId(int id);
	Type getType() const;
	void setType(Type type);
	int getAtk() const;
	void setAtk(int atk);
	int getAtkCost() const;
	void setAtkCost(int atk);
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
	Player *getPlayer() const;
	void setPlayer(Player *player);
	Tile *getTile() const;
	void setTile(Tile *tile);
	int getRatk() const;
	void setRatk(int ratk);

	void takeDamage(int v);
	bool canMoveOn(Tile *t) const;
	bool canMoveOn(int x, int y) const;
	bool canHit(Unit *u) const;
	bool canHit(Tile *t) const;
	bool canHit(int x, int y) const;
	int distanceFrom(Tile *t) const;
	int distanceFrom(int x, int y) const;
	bool isDead() const;
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

#endif /* SRC_UNIT_H_ */
