/*
 * View.hpp
 */

#ifndef VIEW_HPP
#define VIEW_HPP

#include "Controller.hpp"
class Controller;

class View {
public:
	View();
	void render(Controller *c);
};

#endif /* VIEW_HPP*/
