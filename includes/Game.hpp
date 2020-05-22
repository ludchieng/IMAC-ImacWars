/*
 * Game.hpp
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "../includes/Controller.hpp"
#include "../includes/View.hpp"
#include "../includes/Vector2i.hpp"
#include "../includes/Vector2d.hpp"

class Controller;

class Game {

public:
    Game(bool againstComputer, bool fullscreen);
    ~Game();

    void reshape();

    void startLoop();
    void handleEvents();
    void update();
    void render();
    void endLoop();
    void quit();

    bool isRunning() const { return m_isRunning; };
    int getWindowWidth();
    int getWindowHeight();

    long int counter = 0;

    static SDL_Renderer *renderer;

private:
    static const unsigned int W_WIDTH = 1300;
    static const unsigned int W_HEIGHT = 900;
    static const char W_TITLE[];

    static const unsigned int MAP_SIZE = 16;

    static const int LOOPRATE = 60;
    static const float GL_VIEW_SIZE;

    float m_wRatio;
    Uint32 m_startTime;

    bool m_isRunning;
    SDL_Window *m_window;
    SDL_GLContext m_gl;
    Controller *c;

    Vector2d coordsSDLtoGL(Vector2i*);
    Vector2d coordsSDLtoGL(int x, int y);
    Vector2i coordsGLtoSDL(Vector2d*);
    Vector2i coordsGLtoSDL(double x, double y);
};

#endif /* GAME_HPP */
