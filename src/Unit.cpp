/*
 * Unit.cpp
 */

#include "../includes/Unit.hpp"


Unit::Unit(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def) {
	m_player = player;
	m_tile = NULL;
	m_hp = hpMax;
	m_hpMax = hpMax;
	m_mp = mpMax;
	m_mpMax = mpMax;
	m_ratk = ratk;
	m_atkcost = atkcost;
	m_atk = atk;
	m_def = def;
}

Unit::~Unit() {
	
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

bool Unit::canStandOn(Tile *t) {
	return Unit::canStandOn(t->getLandType());
}

bool Unit::canStandOn(Land::Type lt) {
	switch (lt) {
		case Land::Type::SHORE:
		case Land::Type::PLAIN:
		case Land::Type::FOREST:
			return true;
		case Land::Type::OCEAN:
		case Land::Type::COAST:
		case Land::Type::MOUNTAIN:
		case Land::Type::PEAK:
			return false;
	}
}