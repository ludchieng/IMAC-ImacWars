/*
 * Color.hpp
 */

#ifndef COLOR_HPP
#define COLOR_HPP

#include <math.h>

class Color {

public:
    Color();
    Color(int r, int g, int b, int a);
    Color(int r, int g, int b);
    ~Color();

    static Color lerp(Color *c1, Color *c2, float min, float max, float value);

    int r;
    int g;
    int b;
    int a;

private:

};

#endif /* COLOR_HPP */
