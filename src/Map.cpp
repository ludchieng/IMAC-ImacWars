/*
 * Map.cpp 
 */

#include "../includes/Map.hpp"

Map::Map() {
	generate();
}

Map::~Map() {
	for (vector<Tile *> row : m_tiles) {
		for (Tile *t : row)
			delete t;
	}
}

void Map::generate() {
	m_tiles = vector<vector<Tile *>>();

	for (int y = 0; y < MAP_ROWS_COUNT; y++) {
		m_tiles.push_back(vector<Tile *>());
		for (int x = 0; x < MAP_COLS_COUNT; x++) {
			Tile *t = new Tile(x, y);
			m_tiles[y].push_back(t);
		}
	}
	generateAltitude();
}

void Map::generateAltitude() {
	srand(time(NULL));
	FastNoise perlin;
	perlin.SetNoiseType(FastNoise::SimplexFractal);
	perlin.SetSeed(rand());
	float alt;
	for (int y = 0; y < getSizeY(); y++) {
		for (int x = 0; x < getSizeX(); x++) {
			alt = perlin.GetNoise(x * ZOOM, y * ZOOM);
			alt += .5;
			m_tiles[x][y]->setAltitude(alt);
		}
	}
}