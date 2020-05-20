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

Tile::Path::Path()
	: tiles(NULL), size(0) {
}

Tile::Path::~Path() {
}

void Tile::Path::add(Tile *t) {
		size++;
		tiles = (Tile**) realloc(tiles, sizeof(Tile*) * size);
		tiles[size-1] = t;
}

int Tile::distanceFrom(Tile *t) const {
	int dx = t->getPosX() - m_pos.x;
	int dy = t->getPosY() - m_pos.y;
	if (dx < 0) {
		dx = -dx;
	}
	if (dy < 0) {
		dy = -dy;
	}
	return dx + dy;
}

int Tile::distanceFrom(int x, int y) const {
	int dx = x - m_pos.x;
	int dy = y - m_pos.y;
	if (dx < 0) {
		dx = -dx;
	}
	if (dy < 0) {
		dy = -dy;
	}
	return dx + dy;
}