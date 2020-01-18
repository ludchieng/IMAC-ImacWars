/*
 * Model.cpp
 */

#include "Model.h"
#include <iostream>
#include <algorithm>

Model::Model() {
	// Create tiles
	m_tiles = vector<vector<Tile*>>();
    for (int y = 0; y < 16 ; y++) {
    	m_tiles.push_back(vector<Tile*>());
    	for (int x = 0; x < 9; x++) {
    		Tile* t = new Tile(x,y);
    		m_tiles[y].push_back(t);
    	}
    }

    // Create players
	m_players = vector<Player*>();
	for (int i = 0; i < 2; i++) {
		Player* p = new Player();
		m_players.push_back(p);

		m_players[i]->m_units = vector<Unit*>();

		// Create units
		for (int j = 0; j < 4; j++) {
			Tile* t = m_tiles[3+i*10][i+1+j*2];
			Unit* u = new Unit(j, *m_players[i]);
			t->setUnit(u);
			u->setTile(t);
			m_players[i]->m_units.push_back(u);
		}
	}
}

Model::~Model() {
	for (vector<Tile*> row : m_tiles) {
		for (Tile* t : row)
			delete t;
	}
	for (Player* p : m_players) {
		for (Unit* u : p->m_units)
			delete u;
		delete p;
	}
}

vector<vector<Tile*>> Model::getTiles() {
	return m_tiles;
}

Unit* Model::getUnit(int x, int y) const {
	if (x < 0 || y < 0 || x >= 9 || y >= 16) {
		throw "No such tile";
	}
	return m_tiles[y][x]->getUnit();
}

void Model::moveUnit(Unit *u, int x, int y) {
	if (x < 0 || y < 0 || x >= 9 || y >= 16) {
		throw "No such tile";
	}
	if (!u->canMoveOn(x, y)) {
		throw "Illegal State";
	}
	// Update unit and tiles
	m_tiles[y][x]->setUnit(u);
	u->getTile()->delUnit();
	u->setTile(m_tiles[y][x]);
}

void Model::attackUnit(Unit *a, Unit *t) {
	if (a->isDead()) {
		throw "Illegal State";
	}
	srand(time(NULL));
	float bonus = 1 + ((float)(rand() % 20))/100;
	int dmgOnTarget    = a->getHp()/a->getHpMax() * a->getAtk() * bonus - t->getDef();
	int dmgOnAssailant = t->getHp()/t->getHpMax() * t->getAtk() - a->getDef();
	t->takeDamage(dmgOnTarget);
	a->takeDamage(dmgOnAssailant);
	if (t->isDead()) {
		this->deleteUnit(t);
	}
	if (a->isDead()) {
		this->deleteUnit(a);
	}
}

void Model::deleteUnit(Unit *u) {
	u->getTile()->delUnit();
	Player* p = u->getPlayer();
	p->m_units.erase(std::remove(p->m_units.begin(), p->m_units.end(), u), p->m_units.end());
	u->die();
}
