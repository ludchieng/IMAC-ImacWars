/*
 * AI.hpp
 */

#ifndef AI_HPP
#define AI_HPP

#include "../includes/Model.hpp"
#include "../includes/Unit.hpp"

class Model;

class AI {

public:
    AI(Model *m);
    ~AI();

    void update();
    void play();

    Unit *nearestReachableUnit(Unit *current, Player *owner);
    Unit *nearestBelligerentUnit(Unit *current);
    int moveTowards(Unit *curr, Unit *e);

    Player *me;
    Player *enemy;

    const int ACTION_INTERVAL = 5;

private:
    Model *m;
    list<Duck*> m_ducks;
    list<Bee*> m_bees;
    list<Rhino*> m_rhinos;
};

#endif /* AI_HPP */
