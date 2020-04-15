/*
 * Model.h
 */

#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include "Exceptions.cpp"
#include "Player.h"
#include "Tile.h"

class Model
{
public:
    typedef enum ArmySize
    {
        CREW,
        FACE_TO_FACE,
        SECTION,
        BATTERY,
        COMPANY,
        BATTALION,
        REGIMENT,
        DIVISION
    } ArmySize;

    typedef struct FightReport
    {
        Unit *assailant;
        Unit *target;
        int dmgOnAssailantBase;      // Estimated damage on assailant
        int dmgOnTargetBase;         // Estimated damage on target
        int varT;                    // Random variation of damage on target
        int varA;                    // Random variation of damage on assailant
        int bonus;                   // Surprise effect damage bonus
        int dmgOnAssailantEffective; // Real damage on assailant
        int dmgOnTargetEffective;    // Real damage on target
        bool couldFightBack;         // Assert target could strike back
        bool shouldHaveDoubleKO;     // Assert both units should have died
    } FightReport;

    static const int MAP_ROWS_COUNT = 16;
    static const int MAP_COLS_COUNT = 9;
    static const int PLAYER_COUNT = 2;

    static const int MAP_ROWS_LABEL[];
    static const char MAP_COLS_LABEL[];

    vector<Player *> m_players;

    Model();
    ~Model();

    vector<vector<Tile *>> getTiles();
    Unit *getUnit(int x, int y) const;

    Player *getPlayerTurn() const;
    void setPlayerTurn(Player *p);
    int getMapRowsCount() const;
    int getMapColsCount() const;

    Player *nextTurn();

    Unit *selectUnit(int x, int y, Player *p);
    void createUnit(Player *p, Tile *t, Unit *u);
    void moveUnit(Unit *u, int x, int y);
    FightReport attackUnit(Unit *assailant, Unit *target);
    void deleteUnit(Unit *u);

    void generateArmies(ArmySize at);

private:
    vector<vector<Tile *>> m_tiles;
    Player *m_playerTurn;
};

#endif /* SRC_MODEL_H_ */
