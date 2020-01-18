/*
 * Unit.h
 */

#ifndef UNIT_H_
#define UNIT_H_

#include "Player.h"
#include "Tile.h"

class Tile;
class Player;

class Unit {
	int m_id;
	Player *m_player;
	Tile *m_tile;
	int m_hp;
	int m_hpMax;
	int m_mp;
	int m_mpMax;
	int m_ratk;
	int m_atk;
	int m_def;

public:
	Unit(int id, Player &player);
	Unit(int id, Player &player,
		int hp, int hpMax,
		int mp, int mpMax,
		int ratk, int atk,
		int def);

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
	Player* getPlayer() const;
	void setPlayer(Player *player);
	Tile* getTile() const;
	void setTile(Tile *tile);
	int getRatk() const;
	void setRatk(int ratk);

	void takeDamage(int v);
	bool canMoveOn(const Tile &t) const;
	bool canMoveOn(int x, int y) const;
	bool isDead() const;
	void die();
};


#endif /* UNIT_H_ */
