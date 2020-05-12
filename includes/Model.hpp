/*
 * Model.hpp
 */

#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include "../includes/Map.hpp"
#include "../includes/Player.hpp"
#include "../includes/Tile.hpp"
#include "../src/Exceptions.cpp"

class Model {
public:
    typedef enum ArmySize {
        CREW, FACE_TO_FACE, SECTION, BATTERY,
        COMPANY, BATTALION, REGIMENT, DIVISION
    } ArmySize;

    typedef struct FightReport {
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

    Model();
    ~Model();

    Map *getMap() { return m_map; }
    Unit* getUnit(int x, int y) const;

    Player* getPlayerTurn() const { return m_playerTurn; }
    void setPlayerTurn(Player *p) { m_playerTurn = p; }

    Player* nextTurn();

    Unit* selectUnit(int x, int y, Player *p);
    void createUnit(Player *p, Tile *t, Unit *u);
    void moveUnit(Unit *u, int x, int y);
    FightReport attackUnit(Unit *assailant, Unit *target);
    void deleteUnit(Unit *u);

    void generateArmies(ArmySize at);

    static const int ROWS_COUNT = 16;
    static const int COLS_COUNT = 9;
    static const int PLAYER_COUNT = 2;

    vector<Player*> m_players;

private:
    Map *m_map;
    Player *m_playerTurn;
};

#endif /* MODEL_HPP */
