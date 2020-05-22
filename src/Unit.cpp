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

void Unit::setTile(Tile *t) {
	m_tile = t;
}

int Unit::distanceFrom(Tile *t) const {
	m_tile->distanceFrom(t);
}

int Unit::distanceFrom(int x, int y) const {
	return m_tile->distanceFrom(x, y);
}

void Unit::move(Tile *t) {
	setMp(getMp() - distanceFrom(t));
	getTile()->delUnit();
	t->setUnit(this);
	setTile(t);
}

void Unit::takeDamage(int dmg) {
	m_hp -= dmg;
	if (m_hp <= 0) {
		die();
	}
}

void Unit::die() {
	m_hp = 0;
	m_mp = 0;
}

bool Unit::canStandOn(Tile *t) {
	return Unit::canStandOn(t->getLandType());
}

bool Unit::canStandOn(Land::Type lt) {
	return lt & getAllowedLandTypes();
}

Land::Type Unit::getAllowedLandTypes() {
	return Land::TYPE_FIELD;
}