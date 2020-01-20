/*
 * Tile.h
 */

#ifndef TILE_H_
#define TILE_H_

#include "Unit.h"
#include "exceptions.cpp"

class Unit;

class Tile
{

public:
	Tile(int posX, int posY);

	int getPosX() const;
	int getPosY() const;
	Unit *getUnit() const;
	void setUnit(Unit *unit);
	void delUnit();
	bool hasUnit() const;

private:
	int m_posX;
	int m_posY;
	Unit *m_unit;
};

#endif /* TILE_H_ */
