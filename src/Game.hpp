/*
 * Game.hpp
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "Controller.hpp"
#include "View.hpp"

class Controller;

class Game {

public:
    Game();
    ~Game();

    void reshape(unsigned int width, unsigned int height);

    void startLoop();
    void handleEvents();
    void update();
    void render();
    void endLoop();
    void quit();

    bool isRunning() const { return m_isRunning; };

private:
    static const unsigned int W_WIDTH = 1280;
    static const unsigned int W_HEIGHT = 720;
    static const char W_TITLE[];

    static const unsigned int GL_BITS_PER_PIXEL = 32;
    static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;
    static const float GL_VIEW_SIZE;

    float m_wRatio;
    Uint32 m_startTime;

    bool m_isRunning;
    SDL_Surface *m_surface;
    Controller *c;
};

#endif /* GAME_HPP */
