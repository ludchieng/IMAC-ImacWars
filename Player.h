/*
 * Player.h
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Unit.h"
#include <vector>
using namespace std;

class Unit;

class Player {
	int m_id;

public:
    vector<Unit*> m_units;
    Player(int id);
    bool hasActiveUnits() const;
    int getId() const;
};

#endif /* PLAYER_H_ */
