/*
 * Model.hpp
 */

#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include "../includes/AI.hpp"
#include "../includes/Map.hpp"
#include "../includes/Player.hpp"
#include "../includes/Tile.hpp"
#include "../src/Exceptions.cpp"

class AI;

class Model {
public:
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

    Model(bool againstComputer, int mapSize);
    ~Model();

    void update(long int counter);
    void nextTurn();

    Map *getMap() { return m_map; }
    Unit* getUnit(int x, int y) const;
    bool isAgainstComputer() const { return m_againstComputer; }
    bool isAI(Player *p) const;
    vector<Player*> getPlayers() const { return m_players; }
    Unit *getSelectedUnit() const { return m_selectedUnit; }
    bool hasSelectedUnit() const { return m_selectedUnit != NULL; }
    list<Tile*> *getSelectedUnitPossibleMoves() { return &m_selectedUnitPossibleMoves; }
    list<Tile*> *getSelectedUnitPossibleAttacks() { return &m_selectedUnitPossibleAttacks; }
    Player* getPlayerTurn() const { return m_playerTurn; }
    void setPlayerTurn(Player *p) { m_playerTurn = p; }

    bool isEndTurn() const;
    bool unitCanMoveOn(Unit *u, Tile *t) const;

    void updateSelectedUnitPossibleMoves();
    void updateSelectedUnitPossibleAttacks();
    int distanceFrom(Unit *u1, Unit *u2, Land::Type lt, bool unitIsWall) const;
    int distanceFrom(Tile *t1, Tile *t2, Land::Type lt, bool unitIsWall) const;

    Unit* selectUnit(int x, int y, Player *p);
    void deselectUnit();
    void assignUnit(Player *p, Tile *t, Unit *u);
    void moveUnit(Unit *u, int x, int y);
    FightReport attackUnit(Unit *assailant, Unit *target);
    void delUnit(Unit *u);

    static const int PLAYER_COUNT = 2;

private:
    bool m_againstComputer;
    Map *m_map;
    Player *m_playerTurn;
    Unit *m_selectedUnit;
    list<Tile*> m_selectedUnitPossibleMoves;
    list<Tile*> m_selectedUnitPossibleAttacks;
    vector<Player*> m_players;
    AI *m_ai;
    int SIZE;
};

#endif /* MODEL_HPP */
