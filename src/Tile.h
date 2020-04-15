/*
 * Tile.h
 */

#ifndef SRC_TILE_H_
#define SRC_TILE_H_

#include <stdlib.h>
#include "Exceptions.cpp"
#include "Unit.h"

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

#endif /* SRC_TILE_H_ */
