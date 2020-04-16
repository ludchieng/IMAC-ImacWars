/*
 * Tile.cpp
 */

#include "Tile.hpp"

Tile::Tile(int posX, int posY) {
	m_posX = posX;
	m_posY = posY;
	m_unit = NULL;
}

Tile::~Tile() {

}

Unit *Tile::getUnit() const {
	if (m_unit == NULL) {
		NoSuchUnit e;
		throw e;
	}
	return m_unit;
}