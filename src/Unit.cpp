/*
 * Unit.cpp
 */

#include "../includes/Unit.hpp"


Unit::Unit(Player *player, int hpMax, int mpMax, int ratk, int atkcost, int atk, int def)
	: Entity() {
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
	pos.x = t->getPosX();
	pos.y = t->getPosY();
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

bool Unit::canMoveOn(Tile *t) const {
	if (!(distanceFrom(t) <= m_mp))
		return false;
	
	if (!canStandOn(t))
		return false;

	return true;
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