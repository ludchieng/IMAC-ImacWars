/*
 * Tile.cpp
 */

#include "../includes/Tile.hpp"

Tile::Tile(int posX, int posY) {
	m_pos.x = posX;
	m_pos.y = posY;
	m_altitude = 0.0;
	m_unit = NULL;
	hash();
}

Tile::Tile(Vector2i pos) {
	m_pos = pos;
	m_altitude = 0.0;
	m_unit = NULL;
	hash();
}

Tile::~Tile() {
}

void Tile::hash() {
	long int tmp = m_pos.x ^ ~(m_pos.y << 4) * (int)(m_altitude * 1000);
	for (int i = 0; i < 5; i++) {
		tmp <<= 6;
		tmp ^= (int)(m_altitude * 1000);
	}
	m_hash = tmp;
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

int Tile::distanceDirectFrom(Tile *t) const {
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

int Tile::distanceDirectFrom(int x, int y) const {
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