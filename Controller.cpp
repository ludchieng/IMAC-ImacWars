/*
 * Controller.cpp
 */

#include "Controller.h"

Controller::Controller()
{
	v = new View();
	m = new Model();
	m_winner = NULL;
	m_sUnit = NULL;
	this->playGame();
}

Controller::~Controller()
{
	delete v;
	delete m;
}

void Controller::playGame()
{
	Player *p = m->getPlayerTurn();
	do
	{
		// Execute a game turn
		string unitCoords;		 // Selected Unit coordinates
		int actionType;				 // Action to achieve (pass, move, attack)
		string actionCoords;	 // Action destination/target coordinates
		bool isValidInput;		 // Assert input string specific pattern
		bool isValidSelection; // Assert player is allowed to select this unit
		bool isValidAction;		 // Assert player is allowed to perform this action
		bool endTurn = false;	// Assert game turn should end after the action
		int x, y;							 // Buffer variables for coordinates

		// Unit selection
		do
		{
			isValidInput = false;
			isValidSelection = false;
			endTurn = false;
			// Read unit coords
			do
			{
				v->render(this);
				cout << "\n\n\nSélectionner: ";
				cin >> unitCoords;
				// Parse input and check conformity
				if (!(isValidInput = Util::isValidCoords(unitCoords)))
				{
					v->m_msg.content = "Saisissez des coordonnées valides (ex. B6)";
					v->m_msg.ansiFormat = View::ANSI_RED;
				}
			} while (!isValidInput);
			v->clearMsg();

			// Parse string input into x,y integers
			Util::a1ToXy(unitCoords, &x, &y);
			try
			{
				m_sUnit = m->selectUnit(x, y, p);
				isValidSelection = true;
			}
			catch (NoSuchUnit &e)
			{
				v->m_msg.content = "La zone ne contient pas d'unité";
				v->m_msg.ansiFormat = View::ANSI_RED;
			}
			catch (IllegalUnitSelection &e)
			{
				v->m_msg.content = "Cette unité ne peut être sélectionnée";
				v->m_msg.ansiFormat = View::ANSI_RED;
			}
		} while (!isValidSelection);

		// Action selection
		string actionInput;
		bool isActionAborted;
		do
		{
			isValidInput = false;
			isValidAction = false;
			isActionAborted = false;
			// Read action to do with the unit
			do
			{
				v->render(this);
				cout << " 1 - Passer le tour" << endl;
				cout << " 2 - Déplacer" << endl;
				cout << " 3 - Attaquer (coûte " << m_sUnit->getAtkCost() << "MP)" << endl;
				cout << "Agissez: ";
				cin >> actionInput;
				// Parse input and check conformity
				if (!(isValidInput = Util::isValidAction(actionInput)))
				{
					v->m_msg.content = "Saisissez une action valide";
					v->m_msg.ansiFormat = View::ANSI_RED;
				}
			} while (!isValidInput);
			v->clearMsg();

			// Parse string unput into integer
			actionType = atoi(actionInput.c_str());
			switch (actionType)
			{
			case 1:
				// Skip turn
				endTurn = true;
				v->clearMsg();
				break;
			case 2:
				// Move unit
				isValidInput = false;
				do
				{
					// Read destination coords
					v->render(this);
					cout << "\n\n Q - Annuler déplacement";
					cout << "\nDéplacer: ";
					cin >> actionCoords;
					if (toupper(actionCoords.at(0)) == 'Q' && actionCoords.size() == 1)
					{
						isActionAborted = true;
					}
					else
					{
						try
						{
							isValidInput = Util::isValidCoords(actionCoords);
							if (isValidInput)
							{
								// Try move unit at x,y
								Util::a1ToXy(actionCoords, &x, &y);
								m->moveUnit(m_sUnit, x, y);
								isValidAction = true;
								v->m_msg.content = "Déplacement de ";
								v->m_msg.content += View::formatANSI(View::formatUnitAbbrLabel(m_sUnit), View::getPlayerColour(m_sUnit->getPlayer()), View::ANSI_CYAN);
								v->m_msg.content += " en ";
								v->m_msg.content += Util::xyToA1(x, y);
								v->m_msg.ansiFormat = View::ANSI_CYAN;
							}
							else
							{
								v->m_msg.content = "Saisissez des coordonnées valides (ex. B6)";
								v->m_msg.ansiFormat = View::ANSI_RED;
							}
						}
						catch (OutOfBound &e)
						{
							v->m_msg.content = "Saisissez des coordonnées valides";
							v->m_msg.ansiFormat = View::ANSI_RED;
						}
						catch (IllegalMoveOutOfRange &e)
						{
							v->m_msg.content = "Zone hors de portée !";
							v->m_msg.ansiFormat = View::ANSI_RED;
						}
						catch (IllegalMoveOccupiedTile &e)
						{
							v->m_msg.content = "Zone déjà occupée !";
							v->m_msg.ansiFormat = View::ANSI_RED;
						}
					}
				} while (!isValidAction && !isActionAborted);
				if (m_sUnit->getMp() == 0)
				{
					// Game turn ends when selected unit can't move anymore
					// One unit move max by game turn
					endTurn = true;
				}
				break;
			case 3:
				// Attack unit
				isValidInput = false;
				do
				{
					// Read target coords
					v->render(this);
					cout << "\n\n Q - Annuler attaque";
					cout << "\nAttaquer: ";
					cin >> actionCoords;
					if (toupper(actionCoords.at(0)) == 'Q' && actionCoords.size() == 1)
					{
						isActionAborted = true;
					}
					else
					{
						// Parse coords
						try
						{
							isValidInput = Util::isValidCoords(actionCoords);
							if (isValidInput)
							{
								Util::a1ToXy(actionCoords, &x, &y);
								// Try to get unit at x,y
								Unit *targetUnit = m->getUnit(x, y);
								// Try attack at x,y
								Model::FightReport fr = m->attackUnit(m_sUnit, targetUnit);
								v->m_fightReport = fr;
								isValidAction = true;
								v->m_msg.content = "Attaque en ";
								v->m_msg.content += Util::xyToA1(x, y);
								;
								v->m_msg.content += " (";
								v->m_msg.content += View::formatANSI(View::formatUnitAbbrLabel(targetUnit), View::getPlayerColour(targetUnit->getPlayer()), View::ANSI_CYAN);
								v->m_msg.content += ")";
								v->m_msg.ansiFormat = View::ANSI_CYAN;
							}
							else
							{
								v->m_msg.content = "Saisissez des coordonnées valides (ex. B6)";
								v->m_msg.ansiFormat = View::ANSI_RED;
							}
						}
						catch (NoSuchUnit &e)
						{
							v->m_msg.content = "Aucune unité dans cette zone";
							v->m_msg.ansiFormat = View::ANSI_RED;
						}
						catch (IllegalAttackOutOfRange &e)
						{
							v->m_msg.content = "Ennemi hors de portée";
							v->m_msg.ansiFormat = View::ANSI_RED;
						}
						catch (IllegalAttackFriendlyFire &e)
						{
							v->m_msg.content = "Tir allié";
							v->m_msg.ansiFormat = View::ANSI_RED;
						}
						catch (IllegalStateNotEnoughMP &e)
						{
							v->m_msg.content = "Pas assez de MP";
							v->m_msg.ansiFormat = View::ANSI_RED;
						}
					}
				} while (!isValidAction && !isActionAborted);
			}
			v->render(this);

			// End of input reading
		} while (!endTurn && m_sUnit->getMp() > 0);
		m_sUnit = NULL;
		v->render(this);

		// End of game turn
		p = m->nextTurn();
	} while (!checkWinner());

	// End of game
	endGame();
}

void Controller::endGame()
{
	v->m_msg.content = "JOUEUR ";
	v->m_msg.content += to_string(m_winner->getId() + 1);
	v->m_msg.content += " a gagné !";
	v->m_msg.ansiFormat = View::ANSI_CYAN;
	m->setPlayerTurn(m_winner);
	v->render(this);
}

bool Controller::checkWinner()
{
	vector<Player *> potentialWinners = m->m_players;
	for (unsigned int i = 0; i < potentialWinners.size();)
	{
		if (potentialWinners[i]->hasActiveUnits() == 0)
		{
			potentialWinners.erase(std::remove(potentialWinners.begin(), potentialWinners.end(), potentialWinners[i]), potentialWinners.end());
		}
		else
		{
			i++;
		}
	}
	if (potentialWinners.size() == 1)
	{
		m_winner = potentialWinners[0];
		return true;
	}
	return false;
}
