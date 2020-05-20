/*
 * Controller.cpp
 */

#include "../includes/Controller.hpp"

Controller::Controller(bool againstComputer, int mapSize) {
	m = new Model(againstComputer, mapSize);
	v = new View(m);
	m_winner = NULL;
	m_sUnit = NULL;
}

Controller::~Controller() {
	delete v;
	delete m;
}

void Controller::handle(SDL_Event *e) {
	switch (e->type) {
	default:
		break;
	}
}

void Controller::handleClick(SDL_Event *e, double x, double y) {
	int xi = (int) (x >= 0.) ? x : x-1;
	int yi = (int) (y >= 0.) ? y : y-1;
	Tile *t = m->getMap()->getTile(xi, yi);
	try {
		if (!m->hasSelectedUnit()) {
			if (t->hasUnit())
				m->selectUnit(xi, yi, m->getPlayerTurn());
			
		} else {
			Unit *su = m->getSelectedUnit();
			Unit *tu = t->getUnit();
			Model::FightReport fr;
			if (!t->hasUnit())
				m->moveUnit(su, xi, yi);
			else if (su == tu)
				m->deselectUnit();
			else if (tu->getPlayer() == su->getPlayer())
				m->selectUnit(xi, yi, m->getPlayerTurn());
			else if (tu->getPlayer() != su->getPlayer()) {
				fr = m->attackUnit(su, tu);
				printf("%d %d %d %d %d %d %d %d %d\n", fr.dmgOnAssailantBase, fr.dmgOnTargetBase,
					fr.varT, fr.varA, fr.bonus, fr.dmgOnAssailantEffective, fr.dmgOnTargetEffective, fr.couldFightBack, fr.shouldHaveDoubleKO);
			}
		}
	} catch (exception *e) {
		printf("%s\n", e->what());
	}
}

void Controller::update() {
	m->update();
}

bool Controller::checkWinner() {
	vector<Player*> players = m->getPlayers();
	for (unsigned int i = 0; i < players.size();) {
		if (players[i]->hasActiveUnits() == 0) {
			players.erase(std::remove(players.begin(), players.end(), players[i]), players.end());
		}
		else {
			i++;
		}
	}
	if (players.size() == 1) {
		m_winner = players[0];
		return true;
	}
	return false;
}
