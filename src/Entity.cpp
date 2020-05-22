/*
 * Entity.cpp
 */

#include "../includes/Entity.hpp"

Entity::Entity(double x, double y, char *text, int ageMax) {
    m_acc = {0.,  0.};
    m_vel = {0., -0.05};
    m_pos = {x, y};
    m_text = text;
    m_ageMax = ageMax;
    m_age = 0;
}

Entity::~Entity() {
    
}

bool Entity::update() {
    m_vel.add(&m_acc);
    m_pos.add(&m_vel);
    m_acc.mult(0);
    return ++m_age <= m_ageMax;
}

void Entity::render(TextureManager *tex) {
    if (m_age > m_ageMax)
        return;
    tex->fontColor3i(255, 255, 255);
    tex->fontOpacity(255 * (m_ageMax-m_age)/(float)m_ageMax);
    tex->fontSize(.5);
    tex->text(m_text, m_pos.x, m_pos.y);
}