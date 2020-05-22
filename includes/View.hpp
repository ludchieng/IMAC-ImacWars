/*
 * View.hpp
 */

#ifndef VIEW_HPP
#define VIEW_HPP

#include "../includes/TextureManager.hpp"
#include "../includes/Entity.hpp"
#include "../includes/Controller.hpp"
#include "../includes/Model.hpp"
#include "../includes/Color.hpp"

class Entity;
class TextureManager;
class Controller;

class View {
public:
	View(Model *m);
	~View();

	list<Entity*> *getEntities() { return &m_entities; }
	void addEntity(Entity *e) { m_entities.push_back(e); }
	void delEntity(Entity *e) { m_entities.remove(e); }

	void render(long int counter);
	void renderMap();
	void renderMapUI();
	void renderAstar();
	void renderUnits();
	void renderTileCursor(int x, int y);

    static const int FRAME_LENGTH = 15;

private:
	Model *m;
	TextureManager *tex;
    long int m_frame = 0;
	list<Entity*> m_entities;

};

#endif /* VIEW_HPP */
