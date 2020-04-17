/*
 * Controller.hpp
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../includes/Game.hpp"
#include "../includes/Model.hpp"
#include "../includes/View.hpp"

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
