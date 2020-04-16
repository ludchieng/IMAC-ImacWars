/*
 * Tile.hpp
 */

#ifndef TILE_HPP
#define TILE_HPP

#include <stdlib.h>
#include "Exceptions.cpp"
#include "Unit.hpp"

class Unit;

class Tile {

public:
	Tile(int posX, int posY);
	~Tile();

	int getPosX() const { return m_posX; }
	int getPosY() const { return m_posY; }
	Unit *getUnit() const;
	void setUnit(Unit *u) { m_unit = u; }
	void delUnit() { m_unit = NULL; }
	bool hasUnit() const { return m_unit != NULL; }

private:
	int m_posX;
	int m_posY;
	Unit *m_unit;
};

#endif /* TILE_HPP */
