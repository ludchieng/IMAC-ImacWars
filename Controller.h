/*
 * Controller.h
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Player.h"
#include "View.h"
#include "Model.h"

class Controller {
    View *m_view;
    Model *m_model;
    bool m_isRunning;
    Player *m_player;

public:
    Controller();
    ~Controller();
    void playGame();
    void endGame();
};

#endif /* CONTROLLER_H_ */
