/*
 * Vector2f.hpp
 */

#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

#include <math.h>

class Vector2f {

public:
    Vector2f();
    Vector2f(double x, double y);
    ~Vector2f();

    double mag();
    void normalize();
    void mult(double n);

    void add(Vector2f *v);
    void sub(Vector2f *v);

    static Vector2f add(Vector2f *a, Vector2f *b);
    static Vector2f sub(Vector2f *a, Vector2f *b);

    double x;
    double y;

private:

};

#endif /* VECTOR2F_HPP */
