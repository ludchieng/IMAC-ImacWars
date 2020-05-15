/*
 * View.hpp
 */

#ifndef VIEW_HPP
#define VIEW_HPP

#include "../includes/TexManager.hpp"
#include "../includes/Controller.hpp"
#include "../includes/Model.hpp"
#include "../includes/Color.hpp"

class Controller;

class View {
public:
	View(Model *m);
	~View();
	void render();
	void renderMap();
	void renderAstar();
	void renderUnits();
	void free();

private:
	Model *m;
	vector<int> m_glTex;
};

#endif /* VIEW_HPP*/
