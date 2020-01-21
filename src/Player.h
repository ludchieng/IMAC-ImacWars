/*
 * Player.h
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <vector>

#include "Unit.h"
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

#endif /* SRC_PLAYER_H_ */
