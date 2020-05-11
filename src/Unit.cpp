/*
 * Unit.cpp
 */

#include "../includes/Unit.hpp"

Unit::Unit(int id, Player *player) {
	m_id = id;
	m_type = Type::Infantry;
	m_player = player;
	m_tile = NULL;
	m_hpMax = 100;
	m_hp = m_hpMax;
	m_mpMax = 4;
	m_mp = m_mpMax;
	m_atkcost = 2;
	m_ratk = 2;
	m_atk = 25;
	m_def = 15;
}

Unit::~Unit() {
	
}

Unit::Unit(int id, Player *player, Type type) {
	m_id = id;
	m_type = type;
	m_player = player;
	m_tile = NULL;
	switch (type) {
	case Type::Infantry:
		m_hpMax = 100;
		m_mpMax = 4;
		m_ratk = 1;
		m_atkcost = 2;
		m_atk = 35;
		m_def = 45;
		break;
	case Type::Artillery:
		m_hpMax = 100;
		m_mpMax = 2;
		m_ratk = 3;
		m_atkcost = 2;
		m_atk = 50;
		m_def = 30;
		break;
	case Type::Tank:
		m_hpMax = 100;
		m_mpMax = 1;
		m_ratk = 2;
		m_atkcost = 1;
		m_atk = 65;
		m_def = 65;
	}
	m_hp = m_hpMax;
	m_mp = m_mpMax;
}

Unit::Unit(int id, Player *player, Type type, int hp, int hpMax, int mp, int mpMax, int ratk, int atkcost, int atk, int def) {
	m_id = id;
	m_type = type;
	m_player = player;
	m_tile = NULL;
	m_hp = hp;
	m_hpMax = hpMax;
	m_mp = mp;
	m_mpMax = mpMax;
	m_ratk = ratk;
	m_atkcost = atkcost;
	m_atk = atk;
	m_def = def;
}

void Unit::takeDamage(int dmg) {
	m_hp -= dmg;
	if (m_hp <= 0) {
		die();
	}
}

int Unit::distanceFrom(Tile *t) const {
	int dx = t->getPosX() - m_tile->getPosX();
	int dy = t->getPosY() - m_tile->getPosY();
	if (dx < 0) {
		dx = -dx;
	}
	if (dy < 0) {
		dy = -dy;
	}
	return dx + dy;
}

int Unit::distanceFrom(int x, int y) const {
	int dx = x - m_tile->getPosX();
	int dy = y - m_tile->getPosY();
	if (dx < 0) {
		dx = -dx;
	}
	if (dy < 0) {
		dy = -dy;
	}
	return dx + dy;
}

void Unit::die() {
	m_hp = 0;
	m_mp = 0;
	m_tile->delUnit();
	m_tile = NULL;
}

bool Unit::canMoveOn(Tile *t) const {
	if (!distanceFrom(t) <= m_mp)
		return false;
	
	if (!canStandOn(t))
		return false;

	return true;
}

bool Unit::canStandOn(Tile *t) const {
	return canStandOn(t->getLandType());
}

bool Unit::canStandOn(LandType lt) const {
	switch (lt) {
		case LandType::SHORE:
		case LandType::PLAIN:
		case LandType::FOREST:
			return true;
		case LandType::OCEAN:
		case LandType::COAST:
		case LandType::MOUNTAIN:
		case LandType::PEAK:
			return false;
	}
}