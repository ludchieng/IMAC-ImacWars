/*
 * Player.hpp
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <algorithm>

#include "../includes/Unit.hpp"
using namespace std;

class Unit;
class Tile;

class Player {

public:

    Player(int id);
    ~Player();

    bool hasActiveUnits() const;
    int getId() const { return m_id; }

    vector<Unit*> *getUnits() { return &m_units; }
    void SetUnit(int i, Unit *u) { m_units[i] = u; }
    void addUnit(Unit *u) { m_units.push_back(u); }
    void delUnit(Unit *u) { m_units.erase(std::remove(m_units.begin(), m_units.end(), u), m_units.end()); }
    Tile *getSpawn() const { return m_spawn; }
    void setSpawn(Tile *t) { m_spawn = t; }

private:
    int m_id;
    Tile *m_spawn;
    vector<Unit*> m_units;
};

#endif /* PLAYER_HPP */
