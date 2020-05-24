/*
 * Controller.cpp
 */

#include "../includes/Controller.hpp"

Controller::Controller(bool againstComputer, int mapSize) {
	m = new Model(againstComputer, mapSize);
	v = new View(m);
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
					
					if (fr.dmgOnTargetEffective != 0) {
						string dmgOnT = to_string(-fr.dmgOnTargetEffective);
						v->addEntity(new Entity(xi, yi, dmgOnT, 50));
					}
					if (fr.dmgOnAssailantEffective != 0) {
						string dmgOnA = to_string(-fr.dmgOnAssailantEffective);
						v->addEntity(new Entity(su->getTile()->getPosX(), su->getTile()->getPosY(), dmgOnA, 40));
					}
				}
			}
		} else {
			// Click is outside the map
			Vector2d cursorPos = {x,y};
			if (v->isHoverBtnNextTurn(cursorPos)
			 && !m->isAI(m->getPlayerTurn()))
				m->nextTurn();
		}
	} catch (exception *e) {
		//printf("%s\n", e->what());
	}
}

void Controller::update(long int counter) {
	v->update();
	m->update(counter);
}

void Controller::render(long int counter) {
	v->render(counter, m_cursorPos);
}