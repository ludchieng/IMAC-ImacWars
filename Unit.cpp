/*
 * Unit.cpp
 */

#include "Unit.h"

Unit::Unit(int id, int player) {
	m_id = id;
	m_player = player;
	m_hpMax = 100;
	m_hp = m_hpMax;
	m_mpMax = 4;
	m_mp = m_mpMax;
	m_ratk = 2;
	m_atk = 25;
	m_def = 15;
}

Unit::Unit(int id, int player, int hp, int hpMax, int mp, int mpMax, int ratk, int atk, int def) {
	m_id = id;
	m_player = player;
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

int Unit::getPlayer() const {
	return m_player;
}

void Unit::setPlayer(int player) {
	m_player = player;
}

int Unit::getRatk() const {
	return m_ratk;
}

void Unit::setRatk(int ratk) {
	m_ratk = ratk;
}

string Unit::toString() {
	stringstream ss;
	ss << "\n\n--- UNIT" << m_id << " ---";
	ss << "\nplayer: ";
	ss << m_player;
	ss << "\nhp: ";
	ss << m_hp;
	ss << "\nhpMax: ";
	ss << m_hpMax;
	ss << "\nmp: ";
	ss << m_mp;
	ss << "\nmpMax: ";
	ss << m_mpMax;
	ss << "\nratk: ";
	ss << m_ratk;
	ss << "\natk: ";
	ss << m_atk;
	ss << "\ndef: ";
	ss << m_def;
	ss << "\n-------------";
	return ss.str();
}


// ---


bool Unit::isDead() {
	return m_hp <= 0;
}

void Unit::takeDamage(int dmg) {
	m_hp -= dmg;
	if (m_hp <= 0) {
		die();
	}
}

void Unit::die() {
	m_hp = 0;
}

void Unit::attack(Unit *&target) {
	if (isDead()) {
		throw "illegal state: unit is dead.";
	}
	srand(time(NULL));
	float bonus = 1 + ((float)(rand() % 20))/100;
	int dmgOnTarget = m_hp/m_hpMax * m_atk * bonus - target->getDef();
	int dmgOnAssailant = target->getHp()/target->getHpMax() * target->getAtk() - getDef();
	target->takeDamage(dmgOnTarget);
	this->takeDamage(dmgOnAssailant);
}
