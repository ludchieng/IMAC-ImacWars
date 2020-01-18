/*
 * Tile.cpp
 */

#include "Tile.h"

Tile::Tile(int posX, int posY, int mpCost) {
	m_posX = posX;
	m_posY = posY;
	m_mpCost = mpCost;
	m_unit = NULL;
}

int Tile::getMpCost() const {
	return m_mpCost;
}

int Tile::getPosX() const {
	return m_posX;
}

int Tile::getPosY() const {
	return m_posY;
}

Unit* Tile::getUnit() {
	return m_unit;
}

void Tile::setUnit(Unit* unit) {
	m_unit = unit;
}

string Tile::toString() {
	stringstream ss;
	ss << "\n\n---- TILE ----";
	ss << "\nposX: " << m_posX;
	ss << "\nposY: " << m_posY;
	return ss.str();
}


// ---


bool Tile::hasUnit() {
	return m_unit != NULL;
}
