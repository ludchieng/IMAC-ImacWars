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
	typedef enum LandType {
		OCEAN, PLAIN, COAST, SHORE, FOREST, MOUNTAIN, PEAK
	} LandType;

	Tile(int posX, int posY);
	~Tile();

	int getPosX() const { return m_posX; }
	int getPosY() const { return m_posY; }
	float getAltitude() const { return m_altitude; }
	void setAltitude(float a) { m_altitude = a; }
	LandType getLandType() const { return m_type; }
	void setLandType(LandType t) { m_type = t; }
	Unit *getUnit() const;
	void setUnit(Unit *u) { m_unit = u; }
	void delUnit() { m_unit = NULL; }
	bool hasUnit() const { return m_unit != NULL; }

private:
	int m_posX;
	int m_posY;
	float m_altitude;
	LandType m_type;
	Unit *m_unit;
};

#endif /* TILE_HPP */
