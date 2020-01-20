/*
 * Controller.h
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Player.h"
#include "View.h"
#include "Model.h"
#include "Util.h"
#include <algorithm>

class View;

class Controller
{
public:
    View *v;
    Model *m;
    Player *m_winner;
    Unit *m_sUnit; // selected Unit

    Controller();
    ~Controller();

    void playGame();
    void endGame();
    bool checkWinner();
};

#endif /* CONTROLLER_H_ */
