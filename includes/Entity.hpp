/*
 * Entity.hpp
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <math.h>
#include "../includes/Vector2d.hpp"

class Entity {
public:
    Entity();
    ~Entity();

    void update();

    Vector2d acc;
    Vector2d vel;
    Vector2d pos;
    Vector2d posSrc;
    Vector2d posDest;
    float posMap[30];

    static const float THRESHOLD_TO_ZERO;
    static const float POS_MAP_EASE_IN_OUT_FACTOR;
    static const int POS_MAP_COUNT = 30;
};

#endif /* ENTITY_HPP */