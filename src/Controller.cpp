/*
 * Controller.cpp
 */

#include "Controller.hpp"

Controller::Controller() {
	v = new View();
	m = new Model();
	m_winner = NULL;
	m_sUnit = NULL;
}

Controller::~Controller() {
	delete v;
	delete m;
}

void Controller::handle(SDL_Event *e) {
	switch (e->type) {
	case SDL_MOUSEBUTTONUP:
		break;
	
	default:
		break;
	}
}

void Controller::update() {
	
}

bool Controller::checkWinner() {
	vector<Player *> potentialWinners = m->m_players;
	for (unsigned int i = 0; i < potentialWinners.size();) {
		if (potentialWinners[i]->hasActiveUnits() == 0) {
			potentialWinners.erase(std::remove(potentialWinners.begin(), potentialWinners.end(), potentialWinners[i]), potentialWinners.end());
		}
		else {
			i++;
		}
	}
	if (potentialWinners.size() == 1) {
		m_winner = potentialWinners[0];
		return true;
	}
	return false;
}
