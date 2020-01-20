/*
 * Player.h
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Unit.h"
#include <vector>
using namespace std;

class Unit;

class Player
{

public:
    vector<Unit *> m_units;
    Player(int id);
    bool hasActiveUnits() const;
    int getId() const;

private:
    int m_id;
};

#endif /* PLAYER_H_ */
