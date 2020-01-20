/*
 * Model.cpp
 */

#include "Model.h"

const int Model::MAP_ROWS_LABEL[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16};

const char Model::MAP_COLS_LABEL[] = {
		'A', 'B', 'C', 'D', 'E',
		'F', 'G', 'H', 'I'};

Model::Model()
{
	// Create tiles
	m_tiles = vector<vector<Tile *>>();
	for (int y = 0; y < MAP_ROWS_COUNT; y++)
	{
		m_tiles.push_back(vector<Tile *>());
		for (int x = 0; x < MAP_COLS_COUNT; x++)
		{
			Tile *t = new Tile(x, y);
			m_tiles[y].push_back(t);
		}
	}

	// Create players
	m_players = vector<Player *>();
	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		Player *p = new Player(i);
		m_players.push_back(p);

		m_players[i]->m_units = vector<Unit *>();
	}
	m_playerTurn = m_players[0];

	generateArmies(ArmySize::CREW);
	//generateArmies(ArmySize::FACE_TO_FACE);
	//generateArmies(ArmySize::SECTION);
	//generateArmies(ArmySize::BATTERY);
	//generateArmies(ArmySize::COMPANY);
}

Model::~Model()
{
	for (vector<Tile *> row : m_tiles)
	{
		for (Tile *t : row)
			delete t;
	}
	for (Player *p : m_players)
	{
		for (Unit *u : p->m_units)
			delete u;
		delete p;
	}
}

vector<vector<Tile *>> Model::getTiles()
{
	return m_tiles;
}

Unit *Model::getUnit(int x, int y) const
{
	if (x < 0 || y < 0 || x >= MAP_COLS_COUNT || y >= MAP_ROWS_COUNT)
	{
		OutOfBound e;
		throw e;
	}
	return m_tiles[y][x]->getUnit();
}

Player *Model::getPlayerTurn() const
{
	return m_playerTurn;
}

void Model::setPlayerTurn(Player *p)
{
	m_playerTurn = p;
}

int Model::getMapRowsCount() const
{
	return m_tiles.size();
}

int Model::getMapColsCount() const
{
	return m_tiles[0].size();
}

Player *Model::nextTurn()
{
	// Reset units for next turn
	for (Player *p : m_players)
	{
		for (Unit *u : p->m_units)
		{
			u->setMp(u->getMpMax());
		}
	}
	// Get to next player's turn
	bool isPlayerFound = false;
	for (unsigned int i = 0; i < m_players.size() && !isPlayerFound; i++)
	{
		if (m_players[i] == m_playerTurn && i != m_players.size() - 1)
		{
			m_playerTurn = m_players[i + 1];
			isPlayerFound = true;
		}
		else
		{
			m_playerTurn = m_players[0];
		}
	}
	return m_playerTurn;
}

Unit *Model::selectUnit(int x, int y, Player *p)
{
	Unit *u = getUnit(x, y);
	if (u->getPlayer() != p)
	{
		IllegalUnitSelection e;
		throw e;
	}
	return u;
}

void Model::createUnit(Player *p, Tile *t, Unit *u)
{
	t->setUnit(u);
	u->setTile(t);
	p->m_units.push_back(u);
}

void Model::moveUnit(Unit *u, int x, int y)
{
	if (x < 0 || y < 0 || x >= MAP_COLS_COUNT || y >= MAP_ROWS_COUNT)
	{
		OutOfBound e;
		throw e;
	}
	if (!u->canMoveOn(x, y))
	{
		IllegalMoveOutOfRange e;
		throw e;
	}
	if (m_tiles[y][x]->hasUnit())
	{
		IllegalMoveOccupiedTile e;
		throw e;
	}
	// Update unit and tiles
	u->setMp(u->getMp() - u->distanceFrom(x, y));
	m_tiles[y][x]->setUnit(u);
	u->getTile()->delUnit();
	u->setTile(m_tiles[y][x]);
}

Model::FightReport Model::attackUnit(Unit *a, Unit *t)
{
	if (a->getMp() < a->getAtkCost())
	{
		IllegalStateNotEnoughMP e;
		throw e;
	}
	if (a->isDead() || t->isDead())
	{
		IllegalState e;
		throw e;
	}
	if (a->getPlayer() == t->getPlayer())
	{
		IllegalAttackFriendlyFire e;
		throw e;
	}
	if (!a->canHit(t))
	{
		IllegalAttackOutOfRange e;
		throw e;
	}
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

	if (t->canHit(a))
	{
		fr.couldFightBack = true;
		dmgOnAssailant = fr.dmgOnAssailantBase + fr.varA;
	}
	else
	{
		fr.couldFightBack = false;
		dmgOnAssailant = 0;
	}

	int tHpAfterFight = t->getHp() - dmgOnTarget;
	int aHpAfterFight = a->getHp() - dmgOnAssailant;

	if (tHpAfterFight > 0 || aHpAfterFight > 0)
	{
		fr.shouldHaveDoubleKO = false;
		t->takeDamage(dmgOnTarget);
		a->takeDamage(dmgOnAssailant);
	}
	else
	{
		// Prevent double K.O.
		fr.shouldHaveDoubleKO = true;
		srand(time(NULL));
		int remainingHP = 1 + (int)(rand() % 9);
		if (tHpAfterFight < aHpAfterFight)
		{
			t->takeDamage(dmgOnTarget);
			a->takeDamage(dmgOnAssailant = a->getHp() - remainingHP);
		}
		else
		{
			t->takeDamage(dmgOnTarget = t->getHp() - remainingHP);
			a->takeDamage(dmgOnAssailant);
		}
	}
	fr.dmgOnTargetEffective = dmgOnTarget;
	fr.dmgOnAssailantEffective = dmgOnAssailant;
	return fr;
}

void Model::deleteUnit(Unit *u)
{
	u->getTile()->delUnit();
	Player *p = u->getPlayer();
	u->die();
	p->m_units.erase(std::remove(p->m_units.begin(), p->m_units.end(), u), p->m_units.end());
}

void Model::generateArmies(Model::ArmySize at)
{
	int uCount = 0;
	Unit *u;
	Player *p;
	switch (at)
	{
	case ArmySize::CREW:

		// Create units player 1
		uCount = 0;
		p = m_players[0];
		u = new Unit(uCount++, p, Unit::Type::Infantry);
		createUnit(p, m_tiles[4][4], u);

		// Create units player 2
		uCount = 0;
		p = m_players[1];
		u = new Unit(uCount++, p, Unit::Type::Infantry);
		createUnit(p, m_tiles[11][4], u);
		break;

	case ArmySize::FACE_TO_FACE:

		// Create units player 1
		uCount = 0;
		p = m_players[0];
		u = new Unit(uCount++, p, Unit::Type::Infantry);
		createUnit(p, m_tiles[4][1], u);
		u = new Unit(uCount++, p, Unit::Type::Artillery);
		createUnit(p, m_tiles[4][4], u);
		u = new Unit(uCount++, p, Unit::Type::Tank);
		createUnit(p, m_tiles[4][7], u);

		// Create units player 2
		uCount = 0;
		p = m_players[1];
		u = new Unit(uCount++, p, Unit::Type::Infantry);
		createUnit(p, m_tiles[7][1], u);
		u = new Unit(uCount++, p, Unit::Type::Artillery);
		createUnit(p, m_tiles[7][4], u);
		u = new Unit(uCount++, p, Unit::Type::Tank);
		createUnit(p, m_tiles[7][7], u);
		break;

	case ArmySize::SECTION:

		// Create units player 1
		uCount = 0;
		p = m_players[0];
		for (int i = 0; i < 4; i++)
		{
			u = new Unit(uCount++, p, Unit::Type::Infantry);
			createUnit(p, m_tiles[2][1 + i], u);
		}

		// Create units player 2
		uCount = 0;
		p = m_players[1];
		for (int i = 0; i < 4; i++)
		{
			u = new Unit(uCount++, p, Unit::Type::Infantry);
			createUnit(p, m_tiles[13][7 - i], u);
		}
		break;

	case ArmySize::BATTERY:

		// Create units player 1
		uCount = 0;
		p = m_players[0];
		u = new Unit(uCount++, p, Unit::Type::Tank);
		createUnit(p, m_tiles[4][4], u);
		for (int i = 0; i < 5; i++)
		{
			u = new Unit(uCount++, p, Unit::Type::Artillery);
			createUnit(p, m_tiles[3][2 + i], u);
		}

		// Create units player 2
		uCount = 0;
		p = m_players[1];
		u = new Unit(uCount++, p, Unit::Type::Tank);
		createUnit(p, m_tiles[11][4], u);
		for (int i = 0; i < 5; i++)
		{
			u = new Unit(uCount++, p, Unit::Type::Artillery);
			createUnit(p, m_tiles[12][6 - i], u);
		}
		break;

	case ArmySize::COMPANY:
		// Create units player 1
		uCount = 0;
		p = m_players[0];
		u = new Unit(uCount++, p, Unit::Type::Artillery);
		createUnit(p, m_tiles[2][6], u);
		u = new Unit(uCount++, p, Unit::Type::Artillery);
		createUnit(p, m_tiles[2][2], u);
		u = new Unit(uCount++, p, Unit::Type::Tank);
		createUnit(p, m_tiles[2][4], u);
		for (int i = 0; i < 4; i++)
		{
			u = new Unit(uCount++, p, Unit::Type::Infantry);
			createUnit(p, m_tiles[1][1 + i * 2], u);
		}

		// Create units player 2
		uCount = 0;
		p = m_players[1];
		u = new Unit(uCount++, p, Unit::Type::Artillery);
		createUnit(p, m_tiles[13][2], u);
		u = new Unit(uCount++, p, Unit::Type::Artillery);
		createUnit(p, m_tiles[13][6], u);
		u = new Unit(uCount++, p, Unit::Type::Tank);
		createUnit(p, m_tiles[13][4], u);
		for (int i = 0; i < 4; i++)
		{
			u = new Unit(uCount++, p, Unit::Type::Infantry);
			createUnit(p, m_tiles[14][7 - i * 2], u);
		}
		break;

	case ArmySize::BATTALION:

		// Create units player 1
		uCount = 0;
		p = m_players[0];

		// Create units player 2
		uCount = 0;
		p = m_players[1];
		break;

	case ArmySize::REGIMENT:

		// Create units player 1
		uCount = 0;
		p = m_players[0];

		// Create units player 2
		uCount = 0;
		p = m_players[1];
		break;

	case ArmySize::DIVISION:

		// Create units player 1
		uCount = 0;
		p = m_players[0];

		// Create units player 2
		uCount = 0;
		p = m_players[1];
		break;
	}
}
