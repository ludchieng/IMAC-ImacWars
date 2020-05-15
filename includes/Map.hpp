/*
 * Map.hpp
 */

#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <math.h>
#include <time.h>
#include <map>

#include "../vendor/FastNoise/FastNoise.h"
#include "../includes/Vector2i.hpp"
#include "../includes/FX.hpp"
#include "../includes/Tile.hpp"
#include "../includes/Unit.hpp"
#include "../includes/Astar.hpp"
#include "../src/Exceptions.cpp"

class Map {

public:
    Map(int playersCount, int sizeX, int sizeY);
    ~Map();

    int getSizeY() const { return m_tiles.size(); }
    int getSizeX() const { return m_tiles[0].size(); }
    Tile *getTile(int x, int y) const { return m_tiles[x][y]; }
    Tile *getTile(Vector2i pos) const { return m_tiles[pos.x][pos.y]; }
    vector<vector<Tile*>> getTiles() const { return m_tiles; }
    Unit *getUnit(int x, int y) const { return NULL; } //TODO
    FX *getFX(int x, int y) const { return NULL; } //TODO
    Tile *getSpawn(int i) { return m_spawns[i]; }

    Tile *getRandTile() const;
    Tile *getRandTile(int distFromBorders) const;
    Tile *getRandTile(Land::Type lt) const;
    Tile *getRandTile(int distFromBorders, Land::Type lt) const;
    Tile *getRandTileNear(Tile *t, int dist, Land::Type lt) const;
    void generate();
    void generateAltitude();

    Tile::Path findPath(Tile *start, Tile *target, Land::Type lt) const;

    static const float LIMIT_OCEAN;
    static const float LIMIT_COAST;
    static const float LIMIT_SHORE;
    static const float LIMIT_PLAIN;
    static const float LIMIT_FOREST;
    static const float LIMIT_MOUNTAIN;
    static const float LIMIT_PEAK;

private:

    int SIZE_X;
    int SIZE_Y;
    static const int ZOOM = 5;
    static const int PLAYERS_SPAWN_MIN_DIST = 14;

    vector<vector<Tile*>> m_tiles;
    vector<Tile*> m_spawns;

    Land::Type getLandTypeFromAltitude(float alt);
    void generateSpawns1vs1();
    bool isValidMap();
    bool isValidAltitudeMap();
    bool isValidConnectedTerrainMap();
};

#endif /* MAP_HPP */
