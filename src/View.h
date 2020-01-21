/*
 * View.h
 */

#ifndef SRC_VIEW_H_
#define SRC_VIEW_H_

#include <iostream>
#include <string>

#include "Controller.h"
#include "exceptions.cpp"
#include "Model.h"
#include "Util.h"
using namespace std;

class Controller;

class View
{

public:
	typedef struct
	{
		int ansiFormat;
		string content;
	} Message;

	static const int ANSI_REGULAR = 0;
	static const int ANSI_BOLD = 1;
	static const int ANSI_DIM = 2;
	static const int ANSI_ITALIC = 3;
	static const int ANSI_UNDERLINE = 4;
	static const int ANSI_BLINK = 5;
	static const int ANSI_HIGHLIGHT = 7;
	static const int ANSI_STRIKETHROUGH = 9;
	static const int ANSI_DOUBLE_UNDERLINE = 21;
	static const int ANSI_BORDERBOTTOM = 52;
	static const int ANSI_BLACK = 90;
	static const int ANSI_RED = 91;
	static const int ANSI_GREEN = 92;
	static const int ANSI_YELLOW = 93;
	static const int ANSI_BLUE = 94;
	static const int ANSI_MAGENTA = 95;
	static const int ANSI_CYAN = 96;
	static const int ANSI_GREY = 97;
	static const int ANSI_WHITE = 98;
	static const int ANSI_H_BLACK = 40;
	static const int ANSI_H_RED = 41;
	static const int ANSI_H_GREEN = 42;
	static const int ANSI_H_YELLOW = 43;
	static const int ANSI_H_BLUE = 44;
	static const int ANSI_H_MAGENTA = 45;
	static const int ANSI_H_CYAN = 46;
	static const int ANSI_H_GREY = 47;

	static const int ANSI_COLOURS[];
	static const int ANSI_H_COLOURS[];
	static const int ANSI_COLOURS_COUNT = 7;

	static const int LINEBREAKS_ON_RENDER_COUNT = 30;

	Message m_msg;
	Model::FightReport m_fightReport;

	View();

	void render(Controller *c);
	string renderHeader(Controller *c);
	string renderMap(Controller *c);
	string renderPanel(Controller *c);
	string renderMsg();

	void clearMsg();

	static string insertANSI(int code);
	static string insertANSI();
	static string formatANSI(char *s, int inner);
	static string formatANSI(string s, int inner);
	static string formatANSI(char *s, int inner, int after);
	static string formatANSI(string s, int inner, int after);

	static string formatUnitAbbrLabel(Unit *u);
	static string formatUnitLabel(Unit *u);

	static int getPlayerColour(Player *p);
	static int getPlayerHColour(Player *p);
};

#endif /* SRC_VIEW_H_*/
