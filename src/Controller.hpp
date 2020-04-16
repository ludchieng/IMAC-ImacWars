/*
 * Controller.hpp
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Game.hpp"
#include "Model.hpp"
#include "View.hpp"

class View;

class Controller {
public:
    View *v;
    Model *m;
    Player *m_winner;
    Unit *m_sUnit; // selected Unit

    Controller();
    ~Controller();

    void handle(SDL_Event *e);
    void update();
    bool checkWinner();
};

#endif /* CONTROLLER_HPP */
