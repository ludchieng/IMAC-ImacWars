/*
 * Player.cpp
 */

#include "../includes/Player.hpp"

Player::Player(int id) {
	m_id = id;
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
