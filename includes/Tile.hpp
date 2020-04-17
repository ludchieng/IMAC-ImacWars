/*
 * Tile.hpp
 */

#ifndef TILE_HPP
#define TILE_HPP

#include <stdlib.h>

#include "../includes/Unit.hpp"
#include "Exceptions.cpp"

class Unit;

class Tile {

public:
	Tile(int posX, int posY);
	~Tile();

	int getPosX() const { return m_posX; }
	int getPosY() const { return m_posY; }
	float getAltitude() const { return m_altitude; }
	void setAltitude(float a) { m_altitude = a; }
	Unit *getUnit() const;
	void setUnit(Unit *u) { m_unit = u; }
	void delUnit() { m_unit = NULL; }
	bool hasUnit() const { return m_unit != NULL; }

private:
	int m_posX;
	int m_posY;
	float m_altitude;
	Unit *m_unit;
};

#endif /* TILE_HPP */
