/*
 * Model.h
 */ 

#ifndef MODEL_H_
#define MODEL_H_

#include "Tile.h"
#include "Player.h"

class Model {
    vector<vector<Tile*>> m_tiles;
    vector<Player*> m_players;
public:
    Model();
    ~Model();
    vector<vector<Tile*>> getTiles();
    Unit* getUnit(int x, int y) const;
    void moveUnit(Unit *u, int x, int y);
    void attackUnit(Unit *assailant, Unit *target);
    void deleteUnit(Unit *u);
};

#endif /* MODEL_H_ */
