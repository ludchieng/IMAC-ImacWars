/*
 * Game.hpp
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include "../includes/Controller.hpp"
#include "../includes/View.hpp"
#include "../includes/MVector.hpp"

class Controller;

class Game {

public:
    Game(bool fullscreen);
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

    static SDL_Renderer *renderer;

private:
    static const unsigned int W_WIDTH = 600;
    static const unsigned int W_HEIGHT = 600;
    static const char W_TITLE[];

    static const unsigned int GL_VIEWPORT_HEIGHT = 20;

    static const Uint32 FRAMERATE = 60;
    static const float GL_VIEW_SIZE;

    float m_wRatio;
    Uint32 m_startTime;

    bool m_isRunning;
    SDL_Window *m_window;
    SDL_GLContext m_gl;
    Controller *c;

    MVector coordsSDLtoGL(MVector*);
    MVector coordsSDLtoGL(int x, int y);
    MVector coordsGLtoSDL(MVector*);
    MVector coordsGLtoSDL(double x, double y);
};

#endif /* GAME_HPP */
