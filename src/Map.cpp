/*
 * Map.cpp 
 */

#include "../includes/Map.hpp"

const float Map::LIMIT_OCEAN = .25;
const float Map::LIMIT_COAST = .28;
const float Map::LIMIT_SHORE = .40;
const float Map::LIMIT_PLAIN = .65;
const float Map::LIMIT_FOREST = .72;
const float Map::LIMIT_MOUNTAIN = .85;
const float Map::LIMIT_PEAK = .95;

Map::Map(int playersCount, int size) {
	m_spawns.reserve(playersCount);
	SIZE_X = size;
	SIZE_Y = size;
	generate();
}

Map::~Map() {
	for (vector<Tile*> row : m_tiles) {
		for (Tile *t : row)
			delete t;
	}
}

vector<vector<Tile*>> Map::getTilesPortion(int x, int y, int maxDist) const {
	if (x < 0 || y < 0 || x >= SIZE_X || y >= SIZE_Y)
		throw new OutOfBound();
	return getTilesPortion(getTile(x, y), maxDist);
}

vector<vector<Tile*>> Map::getTilesPortion(Tile *t, int maxDist) const {
	int minX = t->getPosX() - maxDist;
	int minY = t->getPosY() - maxDist;
	int maxX = t->getPosX() + maxDist;
	int maxY = t->getPosY() + maxDist;
	minX = (minX < 0) ? 0 : minX;
	maxX = (maxX > SIZE_X-1) ? SIZE_X-1 : maxX;
	minY = (minY < 0) ? 0 : minY;
	maxY = (maxY > SIZE_Y-1) ? SIZE_Y-1 : maxY;
	int sizeX = maxX - minX + 1;
	int sizeY = maxY - minY + 1;
	vector<vector<Tile*>> res(sizeX);
	for (int i = 0; i < sizeX; i++) {
		vector<Tile*> tmp(sizeY);
		res[i] = tmp;
		for (int j = 0; j < sizeY; j++) {
			res[i][j] = getTile(i + minX, j + minY);
		}
	}
	return res;
}

list<Tile*> Map::getTilesArea(int x, int y, int maxDist) const {
	if (x < 0 || y < 0 || x >= SIZE_X || y >= SIZE_Y)
		throw new OutOfBound();
	return getTilesArea(getTile(x, y), maxDist);
}

list<Tile*> Map::getTilesArea(Tile *t, int maxDist) const {
	return getTilesArea(t, maxDist, Land::TYPE_ALL);
}

list<Tile*> Map::getTilesArea(Tile *t, int maxDist, Land::Type ltf) const {
	return getTilesArea(t, maxDist, ltf, false);
}

list<Tile*> Map::getTilesArea(Tile *t, int maxDist, Land::Type ltf, bool disallowOccupiedTiles) const {
	list<Tile*> res;
	vector<vector<Tile*>> p = getTilesPortion(t, maxDist);
	Tile * topLeft = p[0][0];
	Tile * bottomRight = p[p.size()-1][p[0].size()-1];
	int minX = topLeft->getPosX();
	int maxX = bottomRight->getPosX();
	int minY = topLeft->getPosY();
	int maxY = bottomRight->getPosY();
	for (int i = minX; i <= maxX; i++) {
		for (int j = minY; j <= maxY; j++) {
			Tile *tmp = getTile(i,j);
			Tile::Path path = findPath(t, tmp, ltf, maxDist, disallowOccupiedTiles);
			if (path.size != 0 && path.size <= maxDist)
				res.push_back(tmp);
		}
	}
	return res;
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
		m_tiles.push_back(vector<Tile*>(SIZE_Y));
		for (int y = 0; y < SIZE_Y; y++) {
			Tile *t = new Tile(x, y);
			m_tiles[x][y] = t;
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
	FastNoise perlin1;
	FastNoise perlin2;
	FastNoise perlin3;
	perlin1.SetNoiseType(FastNoise::SimplexFractal);
	perlin1.SetSeed(rand());
	perlin2.SetNoiseType(FastNoise::SimplexFractal);
	perlin2.SetSeed(rand());
	perlin3.SetNoiseType(FastNoise::SimplexFractal);
	perlin3.SetSeed(rand());
	float alt;
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			// Oui bon c'est un peu le bordel mais on fait comme on peut hein
			alt = perlin1.GetNoise(x * ZOOM, y * ZOOM);
			alt += perlin2.GetNoise(x * ZOOM * 1.3, y * ZOOM * 1.3) * 9/10 + 0.1;
			alt = (alt > 1) ? .99 : alt;
			alt = (alt < -1) ? -.99 : alt;
			alt /= 2;
			alt += 0.5;
			float am = 1.8;
			alt = pow(pow(alt * 2, am) / 2, 1.0/am) + 0.0;
			alt = alt - 0.6/(x+3) - 0.6/(y+3);
			alt = alt + 0.6/(x-3-SIZE_X) + 0.6/(y-3-SIZE_Y);
			alt = (alt < LIMIT_SHORE || alt > LIMIT_PLAIN) ? alt : alt + (.1 + perlin3.GetNoise(x * ZOOM * 1.8, y * ZOOM * 1.8) * .1);
			alt = (alt < LIMIT_PLAIN || alt > LIMIT_FOREST) ? alt : (perlin3.GetNoise(x * ZOOM * 1.8, y * ZOOM * 1.8) > 0.3) ? LIMIT_PLAIN + 0.1 * perlin3.GetNoise(x * ZOOM * 1.8, y * ZOOM * 1.8) : alt;
			alt = (alt <= LIMIT_FOREST) ? alt : alt - (.05 + perlin3.GetNoise(x * ZOOM * 2, y * ZOOM * 2) * .1);

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
	
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
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

	if (waterRate > 0.60)
		return false;
	if (waterRate < 0.15)
		return false;
	if (mountainousRate / practicableRate > 0.40)
		return false;
	if (practicableRate < 0.40)
		return false;
	if (ltRate[Land::Type::FOREST] < 0.15)
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
		int margin = PLAYERS_SPAWN_MIN_DIST_MARGIN;
		int distFromBorders = PLAYERS_SPAWN_MIN_DIST_FROM_BORDERS;
		do {
			t1 = getRandTile(distFromBorders, Land::TYPE_FIELD);
			t2 = getRandTile(distFromBorders, Land::TYPE_FIELD);
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
	return findPath(start, target, ltf, 0, false);
}

Tile::Path Map::findPath(Tile *start, Tile *target, Land::Type ltf, int maxDist, bool unitIsWall) const {
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
			Tile * t = getTile(i,j);
            bool isWall = !(ltf & t->getLandType());
			isWall |= (unitIsWall && t->hasUnit());
			isWall |= (maxDist != 0 && start->distanceFrom(t) > maxDist);
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