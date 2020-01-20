/*
 * View.cpp
 */

#include "View.h"

const int View::ANSI_COLOURS[] = {
		View::ANSI_YELLOW, View::ANSI_GREEN,
		View::ANSI_MAGENTA, View::ANSI_BLUE,
		View::ANSI_RED, View::ANSI_CYAN, View::ANSI_GREY};

const int View::ANSI_H_COLOURS[] = {
		View::ANSI_H_YELLOW, View::ANSI_H_GREEN,
		View::ANSI_H_MAGENTA, View::ANSI_H_BLUE,
		View::ANSI_H_RED, View::ANSI_H_CYAN,
		View::ANSI_H_GREY};

View::View()
{
	m_msg.ansiFormat = ANSI_CYAN;
	m_msg.content = "Début de partie !";
}

void View::render(Controller *c)
{
	for (int i = 0; i < LINEBREAKS_ON_RENDER_COUNT; i++)
	{
		cout << endl;
	}
	cout << this->renderHeader(c) << endl;
	cout << this->renderMap(c) << endl;
	cout << this->renderPanel(c) << endl;
	cout << this->renderMsg() << endl;
}

string View::renderHeader(Controller *c)
{
	Model *m = c->m;
	string res;
	res += "\n  JOUEUR ";
	res += to_string(1 + m->getPlayerTurn()->getId());
	res = Util::leftPad(res, 55);
	res = Util::rghtPad(res, 88);
	res = formatANSI(res, getPlayerHColour(m->getPlayerTurn()), 0);
	return res;
}

string View::renderMap(Controller *c)
{
	Model *m = c->m;
	string res;
	res += insertANSI(View::ANSI_MAGENTA);
	res += "    |";
	for (int i = 0; i < m->MAP_COLS_COUNT; i++)
	{
		res += ' ';
		res += m->MAP_COLS_LABEL[i];
		res += " |";
	}
	res += '\n';

	for (int i = 0; i < m->MAP_ROWS_COUNT; i++)
	{
		res += " ";
		res += Util::leftPad(to_string(i + 1), 2);
		res += " |";
		for (int j = 0; j < m->MAP_COLS_COUNT; j++)
		{
			string temp2;
			try
			{
				Unit *u = m->getTiles()[i][j]->getUnit();
				temp2 += formatUnitAbbrLabel(u);
				temp2 = formatANSI(temp2, getPlayerColour(u->getPlayer()), View::ANSI_MAGENTA);
			}
			catch (NoSuchUnit &e)
			{
				temp2 += "   ";
			}
			temp2 += '|';
			res += temp2;
		}
		res += ' ';
		res += Util::rghtPad(to_string(i + 1), 2);
		res += '\n';
	}
	res += insertANSI();
	return res;
}

string View::renderPanel(Controller *c)
{
	Model *m = c->m;
	string res;
	res += "--------------------------------------------\n";
	for (Player *p : m->m_players)
	{
		string temp = insertANSI(getPlayerColour(p));
		temp += "JOUEUR ";
		temp += to_string(p->getId() + 1);
		if (p == m->getPlayerTurn())
		{
			temp += ' ';
			temp += insertANSI(getPlayerHColour(p));
			temp += " ";
			temp += insertANSI();
			temp += insertANSI(getPlayerColour(p));
			temp = Util::rghtPad(temp, 43);
		}
		else
		{
			temp = Util::rghtPad(temp, 30);
		}
		temp += "HP  MP    ATK  DEF\n";
		temp += insertANSI();
		res += temp;

		if (p != m->getPlayerTurn())
		{
			res += insertANSI(ANSI_DIM);
		}

		for (Unit *u : p->m_units)
		{
			res += ' ';
			if (!u->isDead())
			{
				Tile *t = u->getTile();
				string temp;
				if (c->m_sUnit == u)
				{
					temp += insertANSI(getPlayerHColour(u->getPlayer()));
					temp += Util::rghtPad(Util::xyToA1(t->getPosX(), t->getPosY()), 3);
					temp += insertANSI();
				}
				else
				{
					temp += Util::rghtPad(Util::xyToA1(t->getPosX(), t->getPosY()), 3);
				}
				res += temp;
			}
			else
			{
				res += "   ";
			}
			res += "    ";
			res += Util::rghtPad(View::formatUnitLabel(u), 12);
			res += "    ";
			res += Util::leftPad(to_string(u->getHp()), 3);
			res += "  ";
			res += Util::leftPad(to_string(u->getMp()), 2);
			res += "  |  ";
			res += Util::leftPad(to_string(u->getAtk()), 2);
			res += "   ";
			res += Util::leftPad(to_string(u->getDef()), 2);
			res += "";
			res += '\n';
		}
		res += '\n';
		if (p != m->getPlayerTurn())
		{
			res += insertANSI();
		}
	}
	res += "--------------------------------------------";
	return res;
}

string View::renderMsg()
{
	return formatANSI(Util::rghtPad(m_msg.content, 43), m_msg.ansiFormat, 0);
}

void View::clearMsg()
{
	m_msg.content = "";
	m_msg.ansiFormat = 0;
}

string View::insertANSI(int code)
{
	string res = "\033[";
	res += to_string(code);
	res += "m";
	return res;
}

string View::insertANSI()
{
	return "\033[m";
}

string View::formatANSI(char *s, int inner)
{
	string res;
	res += insertANSI(inner);
	res += s;
	res += insertANSI();
	return res;
}

string View::formatANSI(string s, int inner)
{
	string res;
	res += insertANSI(inner);
	res += s;
	res += insertANSI();
	return res;
}

string View::formatANSI(char *s, int inner, int after)
{
	string res;
	res += insertANSI(inner);
	res += s;
	res += insertANSI(after);
	return res;
}

string View::formatANSI(string s, int inner, int after)
{
	string res;
	res += insertANSI(inner);
	res += s;
	res += insertANSI(after);
	return res;
}

string View::formatUnitAbbrLabel(Unit *u)
{
	string res;
	switch (u->getType())
	{
	case Unit::Type::Infantry:
		res += "IN";
		break;
	case Unit::Type::Artillery:
		res += "AR";
		break;
	case Unit::Type::Tank:
		res += "TK";
	}
	res += to_string(u->getId() + 1);
	return res;
}

string View::formatUnitLabel(Unit *u)
{
	string res;
	switch (u->getType())
	{
	case Unit::Type::Infantry:
		res += "Infanterie ";
		break;
	case Unit::Type::Artillery:
		res += "Artillerie ";
		break;
	case Unit::Type::Tank:
		res += "Tank ";
	}
	res += to_string(u->getId() + 1);
	return res;
}

int View::getPlayerColour(Player *p)
{
	return ANSI_COLOURS[p->getId() % ANSI_COLOURS_COUNT];
}

int View::getPlayerHColour(Player *p)
{
	return ANSI_H_COLOURS[p->getId() % ANSI_COLOURS_COUNT];
}
