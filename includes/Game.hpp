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

class Controller;

class Game {

public:
    Game(bool fullscreen);
    ~Game();

    void startLoop();
    void handleEvents();
    void update();
    void render();
    void endLoop();
    void quit();

    bool isRunning() const { return m_isRunning; };

    static SDL_Renderer *renderer;

private:
    static const unsigned int W_WIDTH = 600;
    static const unsigned int W_HEIGHT = 600;
    static const char W_TITLE[];

    static const Uint32 FRAMERATE = 60;
    static const float GL_VIEW_SIZE;

    float m_wRatio;
    Uint32 m_startTime;

    bool m_isRunning;
    SDL_Window *m_window;
    SDL_GLContext m_gl;
    Controller *c;
};

#endif /* GAME_HPP */
