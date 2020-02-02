/*
 * Controller.h
 */

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include <stdlib.h>
#include <algorithm>
#include "Model.h"
#include "Player.h"
#include "Util.h"
#include "View.h"

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

#endif /* SRC_CONTROLLER_H_ */
