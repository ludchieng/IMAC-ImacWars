/*
 * MVector.cpp
 */
#include "../includes/MVector.hpp"

MVector::MVector() {
    this->x = 0;
    this->y = 0;
}

MVector::MVector(double x, double y) {
    this->x = x;
    this->y = y;
}

MVector::~MVector() {

}

double MVector::mag() {
    return pow( x*x + y*y, 0.5);
}

void MVector::normalize() {
    mult(1/mag());
}

void MVector::mult(double n) {
    x *= n;
    y *= n;
}

void MVector::add(MVector *v) {
    x += v->x;
    y += v->y;
}
void MVector::sub(MVector *v) {
    x -= v->x;
    y -= v->y;
}

MVector MVector::add(MVector *a, MVector *b) {
    MVector res;
    res.x = a->x + b->x;
    res.y = a->y + b->y;
    return res;
}

MVector MVector::sub(MVector *a, MVector *b) {
    MVector res;
    res.x = a->x - b->x;
    res.y = a->y - b->y;
    return res;
}