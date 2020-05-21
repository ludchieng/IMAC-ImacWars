/*
 * Entity.cpp
 */

#include "../includes/Entity.hpp"

const float Entity::THRESHOLD_TO_ZERO = 0.01;
const float Entity::POS_MAP_EASE_IN_OUT_FACTOR = 2;

Entity::Entity() {
    for (int i = 0; i < POS_MAP_COUNT; i++) {
        float x = i / (float) (POS_MAP_COUNT-1);
        float a = POS_MAP_EASE_IN_OUT_FACTOR;
        posMap[i] = pow(x, a) / (pow(x, a) + pow(1-x, a));
        //printf("%f\n", posMap[i]);
    }
    //printf("\n");
}

Entity::~Entity() {
    
}

void Entity::update() {
    Vector2d delta = Vector2d::sub(&posDest, &pos);
    if (delta.mag() != 0) {
        if (delta.mag() < THRESHOLD_TO_ZERO) {
            pos.x = posDest.x;
            pos.y = posDest.y;
            posSrc = posDest;
        } else {
            Vector2d trajectory = Vector2d::sub(&posDest, &posSrc);
            
        }
    } else {
        posSrc = posDest;
    }
}