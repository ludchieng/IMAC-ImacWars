/*
 * Tile.cpp
 */

#include "Tile.h"

Tile::Tile(int posX, int posY)
{
	m_posX = posX;
	m_posY = posY;
	m_unit = NULL;
}

int Tile::getPosX() const
{
	return m_posX;
}

int Tile::getPosY() const
{
	return m_posY;
}

Unit *Tile::getUnit() const
{
	if (m_unit == NULL)
	{
		NoSuchUnit e;
		throw e;
	}
	return m_unit;
}

void Tile::setUnit(Unit *u)
{
	m_unit = u;
}
void Tile::delUnit()
{
	m_unit = NULL;
}

bool Tile::hasUnit() const
{
	return m_unit != NULL;
}
