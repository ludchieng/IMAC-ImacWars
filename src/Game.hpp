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

class Game {

public:
    Game();
    ~Game();

    void init();
    void handleEvents();
    void update();
    void render();
    void quit();

    bool isRunning();

private:
    bool isrunning;
    SDL_Surface *surface;
    Controller *c;
    View *v;
};

#endif /* GAME_HPP */