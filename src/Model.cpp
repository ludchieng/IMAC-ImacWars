/*
 * Model.cpp
 */

#include "../includes/Model.hpp"

Model::Model(bool againstComputer, int mapSize) {
	SIZE = mapSize;
	bool isSuccess = false;
	m_selectedUnit = NULL;
	do {
		try {
			m_map = new Map(PLAYER_COUNT, SIZE);
			m_players = vector<Player*>(PLAYER_COUNT);

			vector<string*> names;
			names.push_back(new string("Jacky La Brute"));
			names.push_back(new string("Myrabelle 2000"));

			// Create player
			for (int i = 0; i < PLAYER_COUNT; i++) {
				Player *p = new Player(i, names[i]);
				p->setSpawn(m_map->getSpawn(i));
				m_players[i] = p;

				// Create player units
				Unit *army[] = {
					new Duck(p), new Duck(p),
					new Duck(p), new Bee(p),
					new Bee(p), new Rhino(p),
				};
				int margin = 0;
				// Create unit spawns
				for (int unitCount = 0; unitCount < 6; ) {
					Tile *t = m_map->getRandTileNear(p->getSpawn(), 2 + margin/10, Land::TYPE_FIELD);
					if (!t->hasUnit())
						assignUnit(p, t, army[unitCount++]);
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
	m_againstComputer = againstComputer;
	m_ai = new AI(this);
}

Model::~Model() {
	for (Player *p : m_players) {
		for (Unit *u : *(p->getUnits()))
			delete u;
		delete p;
	}
}

bool Model::isAI(Player *p) const {
	return isAgainstComputer() && p == m_ai->me;
}

void Model::update(long int counter) {
	if (isEndTurn())
		nextTurn();
	if (isAgainstComputer()
	 && m_playerTurn == m_ai->me
	 && counter % m_ai->ACTION_INTERVAL == 0) {
		m_ai->update();
		m_ai->play();
	 }
}

void Model::nextTurn() {
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
		list<Unit*> *units = m_playerTurn->getUnits();
		for (Unit *u : *units) {
			if (u->getMp() > 0)
				return false;
		}
		return true;
	}
}

bool Model::unitCanMoveOn(Unit *u, Tile *t) const {
	if (!(u->distanceDirectFrom(t) <= u->getMp()))
		return false;
	if (!u->canStandOn(t))
		return false;
	Tile::Path p = m_map->findPath(u->getTile(), t, u->getAllowedLandTypes(), u->getMpMax(), true);
	return p.size != 0;
}

void Model::updateSelectedUnitPossibleMoves() {
	Unit *su = m_selectedUnit;
	m_selectedUnitPossibleMoves.clear();
	if (su != NULL)
		m_selectedUnitPossibleMoves = m_map->getTilesArea(su->getTile(), su->getMp(), su->getAllowedLandTypes(), true);
}

void Model::updateSelectedUnitPossibleAttacks() {
	Unit *su = m_selectedUnit;
	m_selectedUnitPossibleAttacks.clear();
	if (su != NULL) {
		Tile *sut = su->getTile();
		int ratk = su->getRatk();
		vector<vector<Tile*>> portion = m_map->getTilesPortion(sut, ratk);
		for (vector<Tile*> col : portion) {
			for (Tile *t : col) {
				if (t->hasUnit()) {
					Unit *tu = t->getUnit();
					if (tu->getPlayer() != su->getPlayer() && su->canAttack(tu)) {
						m_selectedUnitPossibleAttacks.push_back(t);
					}
				}
			}
		}
	}
}

int Model::distanceFrom(Unit *u1, Unit *u2, Land::Type lt, bool unitIsWall) const {
	distanceFrom(u1->getTile(), u2->getTile(), lt, unitIsWall);
}

int Model::distanceFrom(Tile *t1, Tile *t2, Land::Type lt, bool unitIsWall) const {
	Tile::Path p = m_map->findPath(t1, t2, lt, 0, unitIsWall);
	return p.size;
}

Unit* Model::selectUnit(int x, int y, Player *p) {
	Unit *u = getUnit(x, y);
	if (u->getPlayer() != p)
		throw new IllegalUnitSelection();
	if (isAgainstComputer() && u->getPlayer() == m_ai->me)
		throw new IllegalUnitSelection();
	m_selectedUnit = u;
	updateSelectedUnitPossibleMoves();
	updateSelectedUnitPossibleAttacks();
	return u;
}

void Model::deselectUnit() {
	m_selectedUnit = NULL;
	updateSelectedUnitPossibleMoves();
	updateSelectedUnitPossibleAttacks();
}

void Model::assignUnit(Player *p, Tile *t, Unit *u) {
	t->setUnit(u);
	u->setTile(t);
	p->addUnit(u);
}

void Model::moveUnit(Unit *u, int x, int y) {
	if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
		throw new OutOfBound();

	Tile *t = m_map->getTile(x, y);
	
	if (!unitCanMoveOn(u, t))
		throw new IllegalMoveOutOfRange();
		
	if (t->hasUnit())
		throw new IllegalMoveOccupiedTile();
		
	// Update unit and tiles
	u->setMp(u->getMp() - distanceFrom(u->getTile(), t, u->getAllowedLandTypes(), true));
	u->getTile()->delUnit();
	t->setUnit(u);
	u->setTile(t);
	if (u->getMp() <= 0)
		deselectUnit();
	else {
		updateSelectedUnitPossibleMoves();
		updateSelectedUnitPossibleAttacks();
	}
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

	srand(time(NULL) % 971);
	fr.bonus = rand() % 20;
	srand(time(NULL) % 3199);
	fr.varT = rand() % 20 - 10;
	srand(time(NULL) % 1371);
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
		} else {
			t->takeDamage(dmgOnTarget = t->getHp() - remainingHP);
			a->takeDamage(dmgOnAssailant);
		}
	}
	fr.dmgOnTargetEffective = dmgOnTarget;
	fr.dmgOnAssailantEffective = dmgOnAssailant;
	if (a->getMp() <= 0)
		deselectUnit();
	if (a->isDead())
		delUnit(a);
	if (t->isDead())
		delUnit(t);
	updateSelectedUnitPossibleMoves();
	updateSelectedUnitPossibleAttacks();
	return fr;
}

void Model::delUnit(Unit *u) {
	u->getTile()->delUnit();
	Player *p = u->getPlayer();
	u->die();
	p->delUnit(u);
}
