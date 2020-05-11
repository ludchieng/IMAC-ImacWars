/*
 * Vector2f.cpp
 */
#include "../includes/Vector2f.hpp"

Vector2f::Vector2f() {
    this->x = 0;
    this->y = 0;
}

Vector2f::Vector2f(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2f::~Vector2f() {

}

double Vector2f::mag() {
    return pow( x*x + y*y, 0.5);
}

void Vector2f::normalize() {
    mult(1/mag());
}

void Vector2f::mult(double n) {
    x *= n;
    y *= n;
}

void Vector2f::add(Vector2f *v) {
    x += v->x;
    y += v->y;
}
void Vector2f::sub(Vector2f *v) {
    x -= v->x;
    y -= v->y;
}

Vector2f Vector2f::add(Vector2f *a, Vector2f *b) {
    Vector2f res;
    res.x = a->x + b->x;
    res.y = a->y + b->y;
    return res;
}

Vector2f Vector2f::sub(Vector2f *a, Vector2f *b) {
    Vector2f res;
    res.x = a->x - b->x;
    res.y = a->y - b->y;
    return res;
}