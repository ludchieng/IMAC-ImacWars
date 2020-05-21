/*
 * View.hpp
 */

#ifndef VIEW_HPP
#define VIEW_HPP

#include "../includes/TextureManager.hpp"
#include "../includes/Controller.hpp"
#include "../includes/Model.hpp"
#include "../includes/Color.hpp"

class TextureManager;
class Controller;

class View {
public:
	View(Model *m);
	~View();
	void render();
	void renderMap();
	void renderMapUI();
	void renderAstar();
	void renderUnits();

private:
	Model *m;
	TextureManager *tex;
};

#endif /* VIEW_HPP*/
