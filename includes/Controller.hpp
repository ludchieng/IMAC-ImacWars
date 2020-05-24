/*
 * Controller.hpp
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../includes/Game.hpp"
#include "../includes/Entity.hpp"
#include "../includes/Model.hpp"
#include "../includes/View.hpp"
#include "../includes/Vector2i.hpp"
#include "../includes/Vector2d.hpp"

class View;

class Controller {
public:
    View *v;
    Model *m;

    Controller(bool againstComputer, int mapSize);
    ~Controller();

	void setCursorPos(Vector2d cp);
	void setCursorPos(double x, double y);

    void handle(SDL_Event *e);
    void handleClick(SDL_Event *e, double x, double y);
    void update(long int counter);
    void render(long int counter);
private:
	Vector2d m_cursorPos;
};

#endif /* CONTROLLER_HPP */
