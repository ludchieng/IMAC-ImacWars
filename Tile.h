/*
 * Tile.h
 */

#ifndef TILE_H_
#define TILE_H_

#include "Unit.h"

class Tile {
	int m_posX;
	int m_posY;
	int m_mpCost;
	Unit* m_unit;

public:
	Tile(int posX, int posY, int mpCost);

	int getMpCost() const;
	int getPosX() const;
	int getPosY() const;
	Unit* getUnit();
	void setUnit(Unit* unit);
	string toString();

	bool hasUnit();

};


#endif /* TILE_H_ */
