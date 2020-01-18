/*
 * Map.cpp
 */

#include "Map.h"

Map::Map(int sizeX, int sizeY) {
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	for (int i=0; i<m_sizeY; i++) {
		for (int j=0; j<m_sizeX; j++) {
			m_tiles.push_back(Tile(i,j,1));
		}
	}
}

Tile* Map::getTile(int x, int y) {
	for (Tile t : m_tiles) {
		cout << t.toString();
		/*if (t.getPosX() == x && t.getPosY() == y) {
			return &t;
		}*/
	}
	return NULL;
}


// ---


string Map::toString() {
	stringstream ss;
	ss << "\n\n";
	for (int i=-1; i<m_sizeY+1; i++) {
		for (int j=-1; j<m_sizeX+1; j++) {
			if ((i==-1 && j==-1)
					|| (i==m_sizeY && j==m_sizeX)
					|| (i==-1 && j==m_sizeX)
					|| (i==m_sizeY && j==-1)) {
				ss << "+";
			} else if (i==-1 || i==m_sizeY) {
				ss << "–";
			} else if (j==-1 || j==m_sizeX) {
				ss << "|";
			} else {
				Tile* t = getTile(i,j);
				if (t->hasUnit()) {
					ss << "X";
				} else {
					ss << " ";
				}
			}
		}
		ss << endl;
	}
	return ss.str();
}
