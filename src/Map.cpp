/*
 * Map.cpp 
 */

#include "../includes/Map.hpp"

const float Map::LIMIT_OCEAN = .28;
const float Map::LIMIT_COAST = .35;
const float Map::LIMIT_SHORE = .45;
const float Map::LIMIT_PLAIN = .65;
const float Map::LIMIT_FOREST = .70;
const float Map::LIMIT_MOUNTAIN = .82;
const float Map::LIMIT_PEAK = .87;

Map::Map(int playersCount) {
	posPlayers.reserve(playersCount);
	generate();
}

Map::~Map() {
	for (vector<Tile*> row : m_tiles) {
		for (Tile *t : row)
			delete t;
	}
}

Tile *Map::getRandTile() const {
	srand((clock() * time(NULL)) % INT32_MAX);
	int rX = rand() % SIZE_X;
	srand((clock() * time(NULL)) % INT32_MAX);
	int rY = rand() % SIZE_Y;
	return getTile(rX, rY);
}

Tile *Map::getRandTile(int landTypesFlags) const {
	Tile* res;
	for (int attempt = 0; attempt < 1000; attempt++) {
		res = getRandTile();
		if (landTypesFlags & res->getLandType())
			return res;
	}
	throw new CouldNotGetRandTileWithinGivenAttempts;
}

Tile *Map::getRandTileNear(Tile *t, int dist, int landTypesFlags) const {
	Tile* res;
	for (int attempt = 0; attempt < 1000; attempt++) {
		res = getRandTile(landTypesFlags);
		Tile::Path p = findPath(t, res, landTypesFlags);
		if (p.size > 0 && p.size <= dist)
			return res;
	}
	throw new CouldNotGetRandTileWithinGivenAttempts;
}

void Map::generate() {
	m_tiles = vector<vector<Tile*>>();

	for (int x = 0; x < SIZE_X; x++) {
		m_tiles.push_back(vector<Tile*>());
		for (int y = 0; y < SIZE_Y; y++) {
			Tile *t = new Tile(x, y);
			m_tiles[x].push_back(t);
		}
	}
	for (int attempt = 0; attempt < 1000; attempt++) {
		generateAltitude();
		generatePosPlayers1vs1();
		if (isValidAltitudeMap())
			return;
	}
	throw new CouldNotGenerateMapWithinGivenAttempts;
}

void Map::generateAltitude() {
	int seed = (clock() * time(NULL)) % INT32_MAX;
	srand(seed);
	FastNoise perlin;
	perlin.SetNoiseType(FastNoise::SimplexFractal);
	perlin.SetSeed(rand());
	float alt;
	for (int y = 0; y < getSizeY(); y++) {
		for (int x = 0; x < getSizeX(); x++) {
			alt = perlin.GetNoise(x * ZOOM, y * ZOOM);
			alt /= 2;
			alt += .5;
			float am = 1.35;
			alt = pow(pow(alt * 2, am) / 2, 1.0/am) + 0.1;
			alt = alt - 0.6/(x+3) - 0.6/(y+3);
			alt = alt + 0.6/(x-3-getSizeX()) + 0.6/(y-3-getSizeY());
			m_tiles[x][y]->setAltitude(alt);
			m_tiles[x][y]->setLandType(getLandTypeFromAltitude(alt));
		}
	}
}

bool Map::isValidAltitudeMap() {
	std::map<LandType, float> ltRate = {
		{LandType::OCEAN, 0}, {LandType::COAST, 0},
		{LandType::SHORE, 0}, {LandType::PLAIN, 0},
		{LandType::FOREST, 0}, {LandType::MOUNTAIN, 0},
		{LandType::PEAK, 0}
	};
	int totalCount = 0;
	
	for (int y = 0; y < getSizeY(); y++) {
		for (int x = 0; x < getSizeX(); x++) {
			LandType lt = m_tiles[x][y]->getLandType();
            ltRate[lt]++;
			totalCount++;
		}
	}

	for (auto i=ltRate.begin(); i!=ltRate.end(); ++i) {
		i->second /= totalCount;
	}

	float waterRate = ltRate[LandType::OCEAN] + ltRate[LandType::COAST];
	float practicableRate = ltRate[LandType::FOREST] + ltRate[LandType::PLAIN] + ltRate[LandType::SHORE];
	float mountainousRate = ltRate[LandType::MOUNTAIN] + ltRate[LandType::PEAK];
	if (waterRate > 0.70)
		return false;
	if (waterRate < 0.22)
		return false;
	if (mountainousRate / practicableRate > 0.40)
		return false;
	if (practicableRate < 0.40)
		return false;
	return true;
}

LandType Map::getLandTypeFromAltitude(float alt) {
	if (alt < LIMIT_OCEAN)
		return LandType::OCEAN;
	if (alt < LIMIT_COAST)
		return LandType::COAST;
	if (alt < LIMIT_SHORE)
		return LandType::SHORE;
	if (alt < LIMIT_PLAIN)
		return LandType::PLAIN;
	if (alt < LIMIT_FOREST)
		return LandType::FOREST;
	if (alt < LIMIT_MOUNTAIN)
		return LandType::MOUNTAIN;
	return LandType::PEAK;
}

void Map::generatePosPlayers1vs1() {
	Tile *t1, *t2;
	Tile::Path path;
	int ltf = LandType::PLAIN | LandType::SHORE | LandType::FOREST;
	for (int attempts = 0; attempts < 1000; attempts++) {
		int margin = 10;
		t1 = getRandTile(ltf);
		do {
			t2 = getRandTile(ltf);;
			path = findPath(t1, t2, ltf);
			if (path.size >= PLAYERS_SPAWN_MIN_DIST + --margin) {
				posPlayers[0] = t1;
				posPlayers[1] = t2;
				return;
			}
		} while (path.size < PLAYERS_SPAWN_MIN_DIST + margin && margin > 0);
	}
	throw new CouldNotGeneratePosPlayersWithinGivenAttempts();
}

Tile::Path Map::findPath(Tile *start, Tile *target, int landTypesFlags) const {
	Tile::Path path;
	if (start == target)
		return path;

    vector<vector<Astar::Node*>> grid(SIZE_X);
    
    for (int j = 0; j < SIZE_Y; j++) {
        vector<Astar::Node*> v(SIZE_X);
        grid[j] = v;
        for (int i = 0; i < SIZE_X; i++) {
            bool isWall = !(landTypesFlags & getTile(i, j)->getLandType());
            grid[j][i] = new Astar::Node(i, j, isWall);
        }
    }

    for (vector<Astar::Node*> v : grid) {
        for (Astar::Node* n : v) {
			if (n->pos->x > 0)
				n->left = grid[n->pos->y][n->pos->x-1];
			if (n->pos->y > 0)
				n->top = grid[n->pos->y-1][n->pos->x];
			if (n->pos->x < grid[0].size()-1)
				n->right = grid[n->pos->y][n->pos->x+1];
			if (n->pos->y < grid.size()-1)
				n->bottom = grid[n->pos->y+1][n->pos->x];
		}
	}

	Astar::Node *astar = Astar::exec(grid,
			grid[start->getPosY()][start->getPosX()],
			grid[target->getPosY()][target->getPosX()]);

	if (astar != NULL) {
		do {
			path.add(getTile(astar->pos->x, astar->pos->y));
			astar = astar->next;
		} while (astar->next != NULL);
	}
    return path;
}