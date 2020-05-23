/*
 * AI.cpp
 */

#include "../includes/AI.hpp"

AI::AI(Model *m) {
    this->m = m;
    me = m->getPlayers()[1];
    enemy = m->getPlayers()[0];
    update();
}

AI::~AI() {
    
}

void AI::update() {
    m_ducks.clear();
    m_bees.clear();
    m_rhinos.clear();
    for (Unit *u : *me->getUnits()) {
        if (NULL != dynamic_cast<Duck*>(u))
            m_ducks.push_back((Duck*) u);
        else if (NULL != dynamic_cast<Bee*>(u))
            m_bees.push_back((Bee*) u);
        else if (NULL != dynamic_cast<Rhino*>(u))
            m_rhinos.push_back((Rhino*) u);
        else
            fprintf(stderr, "Failed to update AI: unknown unit type\n");
    }
}

void AI::play() {
    int moves = 0;
    if (!m_rhinos.empty()) {
        for (Unit *u : m_rhinos) {
            Unit *n = nearestReachableUnit(u, enemy);
            if (n != NULL && u->canAttack(n))
                m->attackUnit(u, n);
            if (n != NULL && u->getMp() > 0) {
                if (moves += moveTowards(u, n) != 0)
                    return;
            }
        }
    }
    if (!m_bees.empty()) {
        for (Unit *u : m_bees) {
            Unit *n = nearestReachableUnit(u, enemy);
            if (n != NULL && u->canAttack(n))
                m->attackUnit(u, n);
            if (n != NULL && u->getMp() > 0) {
                if (moves += moveTowards(u, n) != 0)
                    return;
            }
        }
    }
    if (!m_ducks.empty()) {
        for (Unit *u : m_ducks) {
            Unit *n = nearestReachableUnit(u, enemy);
            if (n != NULL && u->canAttack(n))
                m->attackUnit(u, n);
            if (n != NULL && u->getMp() > 0) {
                if (moves += moveTowards(u, n) != 0)
                    return;
            }
        }
    }
    if (moves == 0)
        m->nextTurn();
}

Unit *AI::nearestReachableUnit(Unit *curr, Player *owner) {
    list<Unit*> *units = owner->getUnits();
    Unit *nearest = NULL;
    int pDist = -1;
    for (Unit *u : *units) {
        int cDist = m->distanceFrom(curr, u, curr->getAllowedLandTypes(), false);
        if (pDist == -1 || cDist < pDist) {
            nearest = u;
            pDist = cDist;
        }
    }
    return nearest;
}

Unit *AI::nearestBelligerentUnit(Unit *curr) {
    list<Unit*> *units = enemy->getUnits();
    Unit *nearest = NULL;
    int pDist = -1;
    for (Unit *u : *units) {
        int cDist = m->distanceFrom(curr, u, u->getAllowedLandTypes(), false);
        if (pDist == -1 || cDist < pDist)
            nearest = u;
    }
    return nearest;
}

int AI::moveTowards(Unit *curr, Unit *e) {
    Tile::Path path = m->getMap()->findPath(curr->getTile(), e->getTile(), curr->getAllowedLandTypes());
    int mpBefore = curr->getMp();
    int idx = mpBefore;
    while (idx > 0) {
        try {
            idx = (idx >= path.size) ? path.size-1 : idx;
            idx = (idx < 0) ? 0 : idx;
            Tile *t = path.tiles[idx];
            m->moveUnit(curr, t->getPosX(), t->getPosY());
            return mpBefore - curr->getMp();
        } catch (exception *e) {
		    //printf("%s\n", e->what());
        }
        idx--;
    }
    return 0;
}