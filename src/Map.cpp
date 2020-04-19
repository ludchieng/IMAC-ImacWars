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
	int attempts = 0;
	do {
		generateAltitude();
		attempts++;
	} while(!isValidMap() && attempts < 1000);
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
			float am = 1.5;
			alt = pow(pow(alt * 2, am) / 2, 1.0/am);
			alt = alt - 0.5/(x+2) - 0.5/(y+2);
			alt = alt + 0.5/(x-2-getSizeX()) + 0.5/(y-2-getSizeY());
			m_tiles[x][y]->setAltitude(alt);
			m_tiles[x][y]->setLandType(getLandTypeFromAltitude(alt));
		}
	}
}

bool Map::isValidMap() {
	return isValidAltitudeMap() && isValidConnectedTerrainMap();
}

bool Map::isValidConnectedTerrainMap() {
	//TODO
	return true;
}

bool Map::isValidAltitudeMap() {
	std::map<Tile::LandType, float> ltRate = {
		{Tile::LandType::OCEAN, 0}, {Tile::LandType::COAST, 0},
		{Tile::LandType::SHORE, 0}, {Tile::LandType::PLAIN, 0},
		{Tile::LandType::FOREST, 0}, {Tile::LandType::MOUNTAIN, 0},
		{Tile::LandType::PEAK, 0}
	};
	int totalCount = 0;
	
	for (int y = 0; y < getSizeY(); y++) {
		for (int x = 0; x < getSizeX(); x++) {
			Tile::LandType lt = m_tiles[x][y]->getLandType();
            ltRate[lt]++;
			totalCount++;
		}
	}

	for (auto i=ltRate.begin(); i!=ltRate.end(); ++i) {
		i->second /= totalCount;
	}

	float waterRate = ltRate[Tile::LandType::OCEAN] + ltRate[Tile::LandType::COAST];
	float practicableRate = ltRate[Tile::LandType::FOREST] + ltRate[Tile::LandType::PLAIN] + ltRate[Tile::LandType::SHORE];
	float mountainousRate = ltRate[Tile::LandType::MOUNTAIN] + ltRate[Tile::LandType::PEAK];
	/*
	printf("Ocean: %d%% | ", (int) (ltRate[Tile::LandType::OCEAN] * 100));
	printf("Coast: %d%% | ", (int) (ltRate[Tile::LandType::COAST] * 100));
	printf("Shore: %d%% | ", (int) (ltRate[Tile::LandType::SHORE] * 100));
	printf("Plain: %d%% | ", (int) (ltRate[Tile::LandType::PLAIN] * 100));
	printf("Forest: %d%% | ", (int) (ltRate[Tile::LandType::FOREST] * 100));
	printf("Mountain: %d%% | ", (int) (ltRate[Tile::LandType::MOUNTAIN] * 100));
	printf("Peak: %d%%\n", (int) (ltRate[Tile::LandType::PEAK] * 100));
	printf("Water: %d%%              | ", (int) (waterRate * 100));
	printf("Practicable: %d%%                     | ", (int) (practicableRate * 100));
	printf("Mountainous: %d%%\n", (int) (mountainousRate * 100));
	*/
	if (waterRate > 0.70)
		return false;
	if (mountainousRate / practicableRate > 0.40)
		return false;
	if (practicableRate < 0.25)
		return false;
	return true;
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