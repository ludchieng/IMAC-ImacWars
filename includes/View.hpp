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

	void drawSquare(double x, double y);
	void drawSquare(double x, double y, int r, int g, int b);
	void drawSquare(double x, double y, int r, int g, int b, int a);
	void drawSquare(double x, double y, int idTex, float scale);
};

#endif /* VIEW_HPP */
