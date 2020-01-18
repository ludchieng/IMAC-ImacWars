/*
 * Unit.cpp
 */

#include "Unit.h"

Unit::Unit(int id, Player &player) {
	m_id = id;
	m_player = &player;
	m_tile = NULL;
	m_hpMax = 100;
	m_hp = m_hpMax;
	m_mpMax = 4;
	m_mp = m_mpMax;
	m_ratk = 2;
	m_atk = 25;
	m_def = 15;
}

Unit::Unit(int id, Player &player, int hp, int hpMax, int mp, int mpMax, int ratk, int atk, int def) {
	m_id = id;
	m_player = &player;
	m_tile = NULL;
	m_hp = hp;
	m_hpMax = hpMax;
	m_mp = mp;
	m_mpMax = mpMax;
	m_ratk = ratk;
	m_atk = atk;
	m_def = def;
}


int Unit::getId() const {
	return m_id;
}

void Unit::setId(int id) {
	m_id = id;
}

int Unit::getAtk() const {
	return m_atk;
}

void Unit::setAtk(int atk) {
	m_atk = atk;
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

bool Unit::canMoveOn(const Tile &t) const {
	int dx = t.getPosX() - m_tile->getPosX();
	int dy = t.getPosY() - m_tile->getPosY();
	if (dx < 0) { dx = -dx; }
	if (dy < 0) { dy = -dy; }
	return (dx + dy) <= m_mp;
}
bool Unit::canMoveOn(int x, int y) const {
	int dx = x - m_tile->getPosX();
	int dy = y - m_tile->getPosY();
	if (dx < 0) { dx = -dx; }
	if (dy < 0) { dy = -dy; }
	return (dx + dy) <= m_mp;
}

void Unit::die() {
	m_hp = 0;
}
