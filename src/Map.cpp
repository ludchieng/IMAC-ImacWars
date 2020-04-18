/*
 * Map.cpp 
 */

#include "../includes/Map.hpp"

const float Map::LIMIT_OCEAN = .30;
const float Map::LIMIT_COAST = .39;
const float Map::LIMIT_SHORE = .49;
const float Map::LIMIT_PLAIN = .70;
const float Map::LIMIT_FOREST = .75;
const float Map::LIMIT_MOUNTAIN = .81;
const float Map::LIMIT_PEAK = .85;

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

	for (int y = 0; y < ROWS_COUNT; y++) {
		m_tiles.push_back(vector<Tile *>());
		for (int x = 0; x < COLS_COUNT; x++) {
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
			alt /= 2;
			alt += .5;
			float am = 3;
			alt = pow(pow(alt * 2, am) / 2, 1.0/am) + 0.1;
			alt = alt - 1.2/(x+2) - 1.2/(y+2);
			alt = alt + 1.2/(x-2-getSizeX()) + 1.2/(y-2-getSizeY());
			m_tiles[x][y]->setAltitude(alt);
			m_tiles[x][y]->setLandType(getLandTypeFromAltitude(alt));
		}
	}
}

Tile::LandType Map::getLandTypeFromAltitude(float alt) {
	if (alt < LIMIT_OCEAN)
		return Tile::LandType::OCEAN;
	if (alt < LIMIT_COAST)
		return Tile::LandType::COAST;
	if (alt < LIMIT_SHORE)
		return Tile::LandType::SHORE;
	if (alt < LIMIT_PLAIN)
		return Tile::LandType::PLAIN;
	if (alt < LIMIT_FOREST)
		return Tile::LandType::FOREST;
	if (alt < LIMIT_MOUNTAIN)
		return Tile::LandType::MOUNTAIN;
	return Tile::LandType::PEAK;
}