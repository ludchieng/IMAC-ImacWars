/*
 * Map.h
 */

#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"
#include <vector>
using namespace std;

class Map {
	int m_sizeX;
	int m_sizeY;
	vector<Tile> m_tiles;

public:
	Map(int sizeX, int sizeY);

	Tile* getTile(int x, int y);

	string toString();

};

#endif /* MAP_H_ */
