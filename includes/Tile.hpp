/*
 * Tile.hpp
 */

#ifndef TILE_HPP
#define TILE_HPP

#include <stdlib.h>

#include "../includes/Vector2i.hpp"
#include "../includes/LandType.hpp"
#include "../includes/Unit.hpp"
#include "../src/Exceptions.cpp"

class Unit;

class Tile {

public:
	Tile(int posX, int posY);
	Tile(Vector2i pos);
	~Tile();

	int getPosX() const { return m_pos.x; }
	int getPosY() const { return m_pos.y; }
	float getAltitude() const { return m_altitude; }
	void setAltitude(float a) { m_altitude = a; }
	LandType getLandType() const { return m_type; }
	void setLandType(LandType t) { m_type = t; }
	Unit *getUnit() const;
	void setUnit(Unit *u) { m_unit = u; }
	void delUnit() { m_unit = NULL; }
	bool hasUnit() const { return m_unit != NULL; }

private:
	Vector2i m_pos;
	float m_altitude;
	LandType m_type;
	Unit *m_unit;
};

#endif /* TILE_HPP */
