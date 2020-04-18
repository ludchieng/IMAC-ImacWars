/*
 * Color.cpp
 */
# include "../includes/Color.hpp"

Color::Color() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->a = 0;
}

Color::Color(int r, int g, int b) {
    this->r = fmax(fmin(r, 255), 0);
    this->g = fmax(fmin(g, 255), 0);
    this->b = fmax(fmin(b, 255), 0);
    this->a = 255;
}

Color::Color(int r, int g, int b, int a) {
    this->r = fmax(fmin(r, 255), 0);
    this->g = fmax(fmin(g, 255), 0);
    this->b = fmax(fmin(b, 255), 0);
    this->a = fmax(fmin(a, 255), 0);
}

Color::~Color() {
    
}

Color Color::lerp(Color *c1, Color *c2, float min, float max, float value) {
    value = fmax(fmin(value, 1.0), 0.0);
    Color res;
    res.r = (c1->r * (max - value) + c2->r * (value - min)) / (max - min);
    res.g = (c1->g * (max - value) + c2->g * (value - min)) / (max - min);
    res.b = (c1->b * (max - value) + c2->b * (value - min)) / (max - min);
    res.a = (c1->a * (max - value) + c2->a * (value - min)) / (max - min);
    return res;
}