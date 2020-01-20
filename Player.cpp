/*
 * Player.cpp
 */

#include "Player.h"

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

int Player::getId() const {
	return m_id;
}
