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
#include "../includes/MVector.hpp"
#include "../includes/Entity.hpp"
#include "../includes/FX.hpp"
#include "../includes/Tile.hpp"
#include "../includes/Unit.hpp"
#include "../src/Exceptions.cpp"

class Map {

public:
    Map();
    ~Map();

    int getSizeY() const { return m_tiles.size(); }
    int getSizeX() const { return m_tiles[0].size(); }
    Tile *getTile(int x, int y) const { return m_tiles[x][y]; }
    Tile *getTile(MVector pos) const { return m_tiles[pos.x][pos.y]; }
    vector<vector<Tile *>> getTiles() const { return m_tiles; }
    Unit *getUnit(int x, int y) const { return NULL; } //TODO
    FX *getFX(int x, int y) const { return NULL; } //TODO

    Tile *getRandTile() const;
    Tile *getRandTile(bool practicableLand) const;
    void generate();
    void generateAltitude();

    static const float LIMIT_OCEAN;
    static const float LIMIT_COAST;
    static const float LIMIT_SHORE;
    static const float LIMIT_PLAIN;
    static const float LIMIT_FOREST;
    static const float LIMIT_MOUNTAIN;
    static const float LIMIT_PEAK;

private:

    static const int ROWS_COUNT = 20;
    static const int COLS_COUNT = 20;
    static const int ZOOM = 5;

    vector<vector<Tile *>> m_tiles;

    Tile::LandType getLandTypeFromAltitude(float alt);
    bool isValidMap();
    bool isValidAltitudeMap();
    bool isValidConnectedTerrainMap();
};

#endif /* MAP_HPP */
