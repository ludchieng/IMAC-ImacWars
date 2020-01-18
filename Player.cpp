/*
 * Player.cpp
 */

#include "Player.h"

Player::Player() {

}

bool Player::hasUnits() const {
	return m_units.size() != 0;
}
