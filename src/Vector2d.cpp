/*
 * Vector2d.cpp
 */
#include "../includes/Vector2d.hpp"

Vector2d::Vector2d() {
    this->x = 0;
    this->y = 0;
}

Vector2d::Vector2d(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2d::~Vector2d() {

}

double Vector2d::mag() {
    return pow( x*x + y*y, 0.5);
}

void Vector2d::normalize() {
    mult(1/mag());
}

void Vector2d::mult(double n) {
    x *= n;
    y *= n;
}

void Vector2d::add(Vector2d *v) {
    x += v->x;
    y += v->y;
}
void Vector2d::sub(Vector2d *v) {
    x -= v->x;
    y -= v->y;
}

Vector2d Vector2d::add(Vector2d *a, Vector2d *b) {
    Vector2d res;
    res.x = a->x + b->x;
    res.y = a->y + b->y;
    return res;
}

Vector2d Vector2d::sub(Vector2d *a, Vector2d *b) {
    Vector2d res;
    res.x = a->x - b->x;
    res.y = a->y - b->y;
    return res;
}