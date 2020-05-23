/*
 * Player.hpp
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include <string>
#include <algorithm>

#include "../includes/Unit.hpp"
using namespace std;

class Unit;
class Tile;

class Player {

public:

    Player(int id, string *name);
    ~Player();

    bool hasActiveUnits() const;
    int getId() const { return m_id; }
    string *getName() const { return m_name; }

    list<Unit*> *getUnits() { return &m_units; }
    void addUnit(Unit *u) { m_units.push_back(u); }
    void delUnit(Unit *u) { m_units.remove(u); }
    Tile *getSpawn() const { return m_spawn; }
    void setSpawn(Tile *t) { m_spawn = t; }

private:
    int m_id;
    Tile *m_spawn;
    list<Unit*> m_units;
    string *m_name;
};

#endif /* PLAYER_HPP */
