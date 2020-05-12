/*
 * Tile.cpp
 */

#include "../includes/Tile.hpp"

Tile::Tile(int posX, int posY) {
	m_pos.x = posX;
	m_pos.y = posY;
	m_altitude = 0.0;
	m_unit = NULL;
}

Tile::Tile(Vector2i pos) {
	m_pos = pos;
	m_altitude = 0.0;
	m_unit = NULL;
}

Tile::~Tile() {

}

Unit *Tile::getUnit() const {
	if (m_unit == NULL)
		throw new NoSuchUnit();
	return m_unit;
}