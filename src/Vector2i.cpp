/*
 * Vector2i.cpp
 */
#include "../includes/Vector2i.hpp"

Vector2i::Vector2i() {
    this->x = 0;
    this->y = 0;
}

Vector2i::Vector2i(int x, int y) {
    this->x = x;
    this->y = y;
}

Vector2i::~Vector2i() {

}

double Vector2i::mag() {
    return pow( x*x + y*y, 0.5);
}

void Vector2i::normalize() {
    mult(1/mag());
}

void Vector2i::mult(double n) {
    x *= n;
    y *= n;
}

void Vector2i::add(Vector2i *v) {
    x += v->x;
    y += v->y;
}
void Vector2i::sub(Vector2i *v) {
    x -= v->x;
    y -= v->y;
}

Vector2i Vector2i::add(Vector2i *a, Vector2i *b) {
    Vector2i res;
    res.x = a->x + b->x;
    res.y = a->y + b->y;
    return res;
}

Vector2i Vector2i::sub(Vector2i *a, Vector2i *b) {
    Vector2i res;
    res.x = a->x - b->x;
    res.y = a->y - b->y;
    return res;
}

Vector2i Vector2i::mult(Vector2i *a, double n) {
    Vector2i res;
    res.x = a->x * n;
    res.y = a->y * n;
    return res;
}