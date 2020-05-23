/*
 * Player.cpp
 */

#include "../includes/Player.hpp"

Player::Player(int id, string *name) {
	m_id = id;
	m_units = list<Unit*>();
	m_name = name;
}

Player::~Player() {
	
}

bool Player::hasActiveUnits() const {
	for (Unit *u : m_units) {
		if (!u->isDead()) {
			return true;
		}
	}
	return false;
}
