/*
 * Vector2d.hpp
 */

#ifndef Vector2d_HPP
#define Vector2d_HPP

#include <math.h>

class Vector2d {

public:
    Vector2d();
    Vector2d(double x, double y);
    ~Vector2d();

    double mag();
    void normalize();
    void mult(double n);

    void add(Vector2d *v);
    void sub(Vector2d *v);

    static Vector2d add(Vector2d *a, Vector2d *b);
    static Vector2d sub(Vector2d *a, Vector2d *b);
    static Vector2d mult(Vector2d *a, double n);

    double x;
    double y;

private:

};

#endif /* Vector2d_HPP */
