/*
 * Player.cpp
 */

#include "Player.hpp"

Player::Player(int id) {
	m_id = id;
}

bool Player::hasActiveUnits() const {
	for (Unit *u : m_units) {
		if (!u->isDead()) {
			return true;
		}
	}
	return false;
}
