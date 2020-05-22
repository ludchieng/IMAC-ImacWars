/*
 * Entity.hpp
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../includes/Game.hpp"
#include "../includes/TextureManager.hpp"
#include "../includes/Vector2i.hpp"
#include "../includes/Vector2d.hpp"

class TextureManager;

class Entity {
public:
    Entity(double x, double y, char *text, int ageMax);
    ~Entity();

    bool update();
    void render(TextureManager *tex);

private:
    Vector2d m_acc;
    Vector2d m_vel;
    Vector2d m_pos;
    int m_ageMax;
    int m_age;
    char *m_text;
};

#endif /* ENTITY_HPP */