/*
 * Controller.cpp
 */

#include "../includes/Controller.hpp"

Controller::Controller(int mapSize) {
	m = new Model(mapSize);
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
	case SDL_MOUSEBUTTONUP:
		break;
	
	default:
		break;
	}
}

void Controller::update() {
	
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
