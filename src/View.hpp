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
	~View();
	void render(Controller *c);
	void free();
};

#endif /* VIEW_HPP*/
