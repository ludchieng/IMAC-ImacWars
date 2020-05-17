/*
 * Model.cpp
 */

#include "../includes/Model.hpp"

Model::Model(int mapSize) {
	SIZE = mapSize;
	bool isSuccess = false;
	m_selectedUnit = NULL;
	do {
		try {
			m_map = new Map(PLAYER_COUNT, SIZE);
			m_players = vector<Player*>(PLAYER_COUNT);

			// Create player
			for (int i = 0; i < PLAYER_COUNT; i++) {
				Player *p = new Player(i);
				p->setSpawn(m_map->getSpawn(i));
				m_players[i] = p;

				// Create player units
				Unit *army[] = {
					new Infantry(p), new Infantry(p),
					new Infantry(p), new Artillery(p),
					new Artillery(p), new Tank(p),
				};
				int margin = 0;
				// Create unit spawns
				for (int unitCount = 0; unitCount < 6; ) {
					Tile *t = m_map->getRandTileNear(p->getSpawn(), 2 + margin/10, Land::TYPE_FIELD);
					if (!t->hasUnit())
						createUnit(p, t, army[unitCount++]);
					margin++;
				}
			}

			m_playerTurn = m_players[0];
			isSuccess = true;

		} catch (exception *e) {
			printf("Map generation failed. Restarting...\n");
			isSuccess = false;
		}
	} while (!isSuccess);
}

Model::~Model() {
	for (Player *p : m_players) {
		for (Unit *u : *(p->getUnits()))
			delete u;
		delete p;
	}
}

void Model::update() {
	if (isEndTurn()) {
		nextTurn();
	}
}

void Model::nextTurn() {
	printf("NEXT TURN!\n");
	m_selectedUnit = NULL;

	// Reset units for next turn
	for (Player *p : m_players)
		for (Unit *u : *(p->getUnits()))
			u->setMp(u->getMpMax());

	// Get to next player's turn
	bool isPlayerFound = false;
	for (unsigned int i = 0; i < m_players.size() && !isPlayerFound; i++) {
		if (m_players[i] == m_playerTurn && i != m_players.size() - 1) {
			m_playerTurn = m_players[i + 1];
			isPlayerFound = true;
		}
		else {
			m_playerTurn = m_players[0];
		}
	}
}

Unit* Model::getUnit(int x, int y) const {
	if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
		throw new OutOfBound();
	return m_map->getTile(x, y)->getUnit();
}

bool Model::isEndTurn() const {
	if (m_playerTurn != NULL) {
		vector<Unit*> *units = m_playerTurn->getUnits();
		for (Unit *u : *units) {
			if (u->getMp() > 0)
				return false;
		}
		return true;
	}
}

Unit* Model::selectUnit(int x, int y, Player *p) {
	Unit *u = getUnit(x, y);
	if (u->getPlayer() != p)
		throw new IllegalUnitSelection();
	m_selectedUnit = u;
	m_selectedUnitPossibleMoves = m_map->getTilesArea(u->getTile(), u->getMp(), u->getAllowedLandTypes(), true);
	return u;
}

void Model::deselectUnit() {
	m_selectedUnit = NULL;
	m_selectedUnitPossibleMoves.clear();
}

void Model::createUnit(Player *p, Tile *t, Unit *u) {
	t->setUnit(u);
	u->setTile(t);
	p->addUnit(u);
}

void Model::moveUnit(Unit *u, int x, int y) {
	if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
		throw new OutOfBound();
	
	if (!u->canMoveOn(m_map->getTile(x, y)))
		throw new IllegalMoveOutOfRange();
		
	if (m_map->getTile(x, y)->hasUnit())
		throw new IllegalMoveOccupiedTile();
		
	// Update unit and tiles
	u->setMp(u->getMp() - u->distanceFrom(x, y));
	m_map->getTile(x, y)->setUnit(u);
	u->getTile()->delUnit();
	u->setTile(m_map->getTile(x, y));
	if (u->getMp() <= 0)
		deselectUnit();
	else
		m_selectedUnitPossibleMoves = m_map->getTilesArea(u->getTile(), u->getMp(), u->getAllowedLandTypes(), true);
}

Model::FightReport Model::attackUnit(Unit *a, Unit *t) {
	if (a->getMp() < a->getAtkCost())
		throw new IllegalStateNotEnoughMP();
		
	if (a->isDead() || t->isDead())
		throw new IllegalState();
		
	if (a->getPlayer() == t->getPlayer())
		throw new IllegalAttackFriendlyFire();
		
	if (!a->canHit(t))
		throw new IllegalAttackOutOfRange();
		
	// Update unit MP
	a->setMp(a->getMp() - a->getAtkCost());

	Model::FightReport fr;
	fr.assailant = a;
	fr.target = t;

	srand(time(NULL));
	fr.bonus = rand() % 20;
	srand(time(NULL));
	fr.varT = rand() % 20 - 10;
	srand(time(NULL));
	fr.varA = rand() % 20 - 10;

	float aPower = a->getAtk() + a->getDef();
	float tPower = t->getAtk() + t->getDef();
	fr.dmgOnTargetBase = a->getAtk() * aPower / tPower;
	fr.dmgOnAssailantBase = t->getAtk() * tPower / aPower;
	int dmgOnTarget = fr.dmgOnTargetBase + fr.varT + fr.bonus;
	int dmgOnAssailant;

	if (t->canHit(a)) {
		fr.couldFightBack = true;
		dmgOnAssailant = fr.dmgOnAssailantBase + fr.varA;
	}
	else {
		fr.couldFightBack = false;
		dmgOnAssailant = 0;
	}

	int tHpAfterFight = t->getHp() - dmgOnTarget;
	int aHpAfterFight = a->getHp() - dmgOnAssailant;

	if (tHpAfterFight > 0 || aHpAfterFight > 0) {
		fr.shouldHaveDoubleKO = false;
		t->takeDamage(dmgOnTarget);
		a->takeDamage(dmgOnAssailant);
	}
	else {
		// Prevent double K.O.
		fr.shouldHaveDoubleKO = true;
		srand(time(NULL));
		int remainingHP = 1 + (int)(rand() % 9);
		if (tHpAfterFight < aHpAfterFight) {
			t->takeDamage(dmgOnTarget);
			a->takeDamage(dmgOnAssailant = a->getHp() - remainingHP);
		}
		else {
			t->takeDamage(dmgOnTarget = t->getHp() - remainingHP);
			a->takeDamage(dmgOnAssailant);
		}
	}
	fr.dmgOnTargetEffective = dmgOnTarget;
	fr.dmgOnAssailantEffective = dmgOnAssailant;
	return fr;
}

void Model::delUnit(Unit *u) {
	u->getTile()->delUnit();
	Player *p = u->getPlayer();
	u->die();
	p->delUnit(u);
}
