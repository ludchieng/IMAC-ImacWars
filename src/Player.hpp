/*
 * Player.hpp
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "Unit.hpp"
using namespace std;

class Unit;

class Player {

public:
    vector<Unit *> m_units;

    Player(int id);
    ~Player();

    bool hasActiveUnits() const;
    int getId() const { return m_id; }

private:
    int m_id;
};

#endif /* PLAYER_HPP */
