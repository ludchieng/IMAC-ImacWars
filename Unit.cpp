/*
 * Unit.cpp
 */

#include "Unit.h"

Unit::Unit(int id, Player* player) {
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

Unit::Unit(int id, Player* player, Type type) {
	m_id = id;
	m_type = type;
	m_player = player;
	m_tile = NULL;
	switch(type) {
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

Unit::Unit(int id, Player* player, Type type, int hp, int hpMax, int mp, int mpMax, int ratk, int atkcost, int atk, int def) {
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


int Unit::getId() const {
	return m_id;
}

void Unit::setId(int id) {
	m_id = id;
}

Unit::Type Unit::getType() const {
	return m_type;
}

void Unit::setType(Type type) {
	m_type = type;
}

int Unit::getAtk() const {
	return m_atk;
}

void Unit::setAtk(int atk) {
	m_atk = atk;
}

int Unit::getAtkCost() const {
	return m_atkcost;
}

void Unit::setAtkCost(int atkcost) {
	m_atkcost = atkcost;
}

int Unit::getDef() const {
	return m_def;
}

void Unit::setDef(int def) {
	m_def = def;
}

int Unit::getHp() const {
	return m_hp;
}

void Unit::setHp(int hp) {
	m_hp = hp;
}

int Unit::getHpMax() const {
	return m_hpMax;
}

void Unit::setHpMax(int hpMax) {
	m_hpMax = hpMax;
}

int Unit::getMp() const {
	return m_mp;
}

void Unit::setMp(int mp) {
	m_mp = mp;
}

int Unit::getMpMax() const {
	return m_mpMax;
}

void Unit::setMpMax(int mpMax) {
	m_mpMax = mpMax;
}

Player* Unit::getPlayer() const {
	return m_player;
}

void Unit::setPlayer(Player *player) {
	m_player = player;
}

Tile* Unit::getTile() const {
	return m_tile;
}

void Unit::setTile(Tile *tile) {
	m_tile = tile;
}

int Unit::getRatk() const {
	return m_ratk;
}

void Unit::setRatk(int ratk) {
	m_ratk = ratk;
}


// ---


bool Unit::isDead() const {
	return m_hp <= 0;
}


void Unit::takeDamage(int dmg) {
	m_hp -= dmg;
	if (m_hp <= 0) {
		die();
	}
}


bool Unit::canMoveOn(Tile* t) const {
	return distanceFrom(t) <= m_mp;
}


bool Unit::canMoveOn(int x, int y) const {
	return distanceFrom(x, y) <= m_mp;
}


bool Unit::canHit(Unit *u) const {
	return distanceFrom(u->getTile()) <= m_ratk;
}


bool Unit::canHit(Tile *t) const {
	return distanceFrom(t) <= m_ratk;
}


bool Unit::canHit(int x, int y) const {
	return distanceFrom(x, y) <= m_ratk;
}


int Unit::distanceFrom(Tile* t) const {
	int dx = t->getPosX() - m_tile->getPosX();
	int dy = t->getPosY() - m_tile->getPosY();
	if (dx < 0) { dx = -dx; }
	if (dy < 0) { dy = -dy; }
	return dx + dy;
}


int Unit::distanceFrom(int x, int y) const {
	int dx = x - m_tile->getPosX();
	int dy = y - m_tile->getPosY();
	if (dx < 0) { dx = -dx; }
	if (dy < 0) { dy = -dy; }
	return dx + dy;
}


void Unit::die() {
	m_hp = 0;
	m_mp = 0;
	m_tile->delUnit();
	m_tile = NULL;
}
