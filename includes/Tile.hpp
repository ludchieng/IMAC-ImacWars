/*
 * Tile.hpp
 */

#ifndef TILE_HPP
#define TILE_HPP

#include <stdlib.h>

#include "../includes/MVector.hpp"
#include "../includes/Unit.hpp"
#include "../src/Exceptions.cpp"

class Unit;

class Tile {

public:
	typedef enum LandType {
		OCEAN, PLAIN, COAST, SHORE, FOREST, MOUNTAIN, PEAK
	} LandType;

	Tile(int posX, int posY);
	Tile(MVector pos);
	~Tile();

	int getPosX() const { return (int) m_pos.x; }
	int getPosY() const { return (int) m_pos.y; }
	float getAltitude() const { return m_altitude; }
	void setAltitude(float a) { m_altitude = a; }
	LandType getLandType() const { return m_type; }
	void setLandType(LandType t) { m_type = t; }
	Unit *getUnit() const;
	void setUnit(Unit *u) { m_unit = u; }
	void delUnit() { m_unit = NULL; }
	bool hasUnit() const { return m_unit != NULL; }

private:
	MVector m_pos;
	float m_altitude;
	LandType m_type;
	Unit *m_unit;
};

#endif /* TILE_HPP */
