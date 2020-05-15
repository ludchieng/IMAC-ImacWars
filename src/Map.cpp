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

Map::Map(int playersCount, int sizeX, int sizeY) {
	m_spawns.reserve(playersCount);
	SIZE_X = sizeX;
	SIZE_Y = sizeY;
	generate();
}

Map::~Map() {
	for (vector<Tile*> row : m_tiles) {
		for (Tile *t : row)
			delete t;
	}
}

Tile *Map::getRandTile() const {
	return getRandTile(0);
}

Tile *Map::getRandTile(int distFromBorders) const {
	srand((clock() * time(NULL)) % INT32_MAX);
	int rX = rand() % (SIZE_X - 2*distFromBorders) + distFromBorders;
	srand((clock() * time(NULL)) % INT32_MAX);
	int rY = rand() % (SIZE_Y - 2*distFromBorders) + distFromBorders;
	return getTile(rX, rY);
}

Tile *Map::getRandTile(Land::Type ltf) const {
	return getRandTile(0, ltf);
}

Tile *Map::getRandTile(int distFromBorders, Land::Type ltf) const {
	Tile* res;
	for (int attempt = 0; attempt < 1000; attempt++) {
		res = getRandTile(distFromBorders);
		if (ltf & res->getLandType())
			return res;
	}
	throw new CouldNotGetRandTileWithinGivenAttempts;
}

Tile *Map::getRandTileNear(Tile *t, int dist, Land::Type ltf) const {
	Tile* res;
	for (int atpt1 = 0; atpt1 < 200; atpt1++) {
		
		for (int atpt2 = 0; atpt2 < 20; atpt2++) {
			srand((clock() * time(NULL)) % INT32_MAX);
			int rX = rand() % (2*dist+1) + t->getPosX() - dist;
			srand((clock() * time(NULL)) % INT32_MAX);
			int rY = rand() % (2*dist+1) + t->getPosY() - dist;

			if (rX < SIZE_X && rX >= 0 && rY < SIZE_Y && rY >= 0) {
				res = getTile(rX, rY);
				if (ltf & res->getLandType())
					break;
			}
		}

		Tile::Path p = findPath(t, res, ltf);
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
		generateSpawns1vs1();
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
	std::map<Land::Type, float> ltRate = {
		{Land::Type::OCEAN, 0}, {Land::Type::COAST, 0},
		{Land::Type::SHORE, 0}, {Land::Type::PLAIN, 0},
		{Land::Type::FOREST, 0}, {Land::Type::MOUNTAIN, 0},
		{Land::Type::PEAK, 0}
	};
	int totalCount = 0;
	
	for (int y = 0; y < getSizeY(); y++) {
		for (int x = 0; x < getSizeX(); x++) {
			Land::Type lt = m_tiles[x][y]->getLandType();
            ltRate[lt]++;
			totalCount++;
		}
	}

	for (auto i=ltRate.begin(); i!=ltRate.end(); ++i)
		i->second /= totalCount;

	float waterRate = ltRate[Land::Type::OCEAN] + ltRate[Land::Type::COAST];
	float practicableRate = ltRate[Land::Type::FOREST] + ltRate[Land::Type::PLAIN] + ltRate[Land::Type::SHORE];
	float mountainousRate = ltRate[Land::Type::MOUNTAIN] + ltRate[Land::Type::PEAK];

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

Land::Type Map::getLandTypeFromAltitude(float alt) {
	if (alt < LIMIT_OCEAN)
		return Land::Type::OCEAN;
	if (alt < LIMIT_COAST)
		return Land::Type::COAST;
	if (alt < LIMIT_SHORE)
		return Land::Type::SHORE;
	if (alt < LIMIT_PLAIN)
		return Land::Type::PLAIN;
	if (alt < LIMIT_FOREST)
		return Land::Type::FOREST;
	if (alt < LIMIT_MOUNTAIN)
		return Land::Type::MOUNTAIN;
	return Land::Type::PEAK;
}

void Map::generateSpawns1vs1() {
	Tile *t1, *t2;
	Tile::Path path;

	for (int attempts = 0; attempts < 1000; attempts++) {
		int margin = 10;
		do {
			t1 = getRandTile(3, Land::TYPE_FIELD);
			t2 = getRandTile(3, Land::TYPE_FIELD);
			path = findPath(t1, t2, Land::TYPE_FIELD);
			if (path.size >= PLAYERS_SPAWN_MIN_DIST + --margin) {
				m_spawns[0] = t1;
				m_spawns[1] = t2;
				return;
			}
		} while (path.size < PLAYERS_SPAWN_MIN_DIST + margin && margin > 0);
	}
	throw new CouldNotGenerateSpawnsWithinGivenAttempts();
}

Tile::Path Map::findPath(Tile *start, Tile *target, Land::Type ltf) const {
	Tile::Path path;
	if (start == target)
		return path;

	// Create A* grid
    vector<vector<Astar::Node*>> grid(SIZE_X);
	for (int i = 0; i < SIZE_X; i++) {
        vector<Astar::Node*> col(SIZE_Y);
        grid[i] = col;
	}

	// Fill grid with nodes
	for (int i = 0; i < SIZE_X; i++) {
		for (int j = 0; j < SIZE_Y; j++) {
            bool isWall = !(ltf & getTile(i, j)->getLandType());
            grid[i][j] = new Astar::Node(i, j, isWall);
		}
	}

	// Link Nodes
    for (vector<Astar::Node*> v : grid) {
        for (Astar::Node* n : v) {
			if (n->pos->x > 0)
				n->left = grid[n->pos->x-1][n->pos->y];
			if (n->pos->y > 0)
				n->top = grid[n->pos->x][n->pos->y-1];
			if (n->pos->x < grid[0].size()-1)
				n->right = grid[n->pos->x+1][n->pos->y];
			if (n->pos->y < grid.size()-1)
				n->bottom = grid[n->pos->x][n->pos->y+1];
		}
	}

	// Perform pathfinding
	Astar::Node *astar = Astar::exec(grid,
			grid[start->getPosX()][start->getPosY()],
			grid[target->getPosX()][target->getPosY()]);

	// Convert A* result to Tile::Path
	if (astar != NULL) {
		do {
			path.add(getTile(astar->pos->x, astar->pos->y));
			astar = astar->next;
		} while (astar->next != NULL);
	}
    return path;
}