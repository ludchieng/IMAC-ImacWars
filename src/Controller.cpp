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

void Controller::setCursorPos(Vector2d cp) {
	setCursorPos(cp.x, cp.y);
}

void Controller::setCursorPos(double x, double y) {
	m_cursorPos.x = x;
	m_cursorPos.y = y;
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
	try {
		if (xi >= 0 && xi < m->getMap()->getSizeX()
		 && yi >= 0 && yi < m->getMap()->getSizeY()) {
			// Handle click on map
			Tile *t = m->getMap()->getTile(xi, yi);
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
					
					v->addEntity(new Entity(xi, yi, "OUCH", 40));
				}
			}
		}
	} catch (exception *e) {
		printf("%s\n", e->what());
	}
}

void Controller::update() {
	m->update();
	list<Entity*> toDelete;
    for (Entity *e : *v->getEntities()) {
		if (!e->update())
			toDelete.push_back(e);
	}
    for (Entity *e : toDelete) {
		v->delEntity(e);
	}
}

void Controller::render(long int counter) {
	v->render(counter);
	int xi = (int) (m_cursorPos.x >= 0.) ? m_cursorPos.x : m_cursorPos.x-1;
	int yi = (int) (m_cursorPos.y >= 0.) ? m_cursorPos.y : m_cursorPos.y-1;
	if (xi >= 0 && xi < m->getMap()->getSizeX()
	 && yi >= 0 && yi < m->getMap()->getSizeY()) {
		Tile *t = m->getMap()->getTile(xi, yi);
		v->renderTileCursor(xi, yi);
	}
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
