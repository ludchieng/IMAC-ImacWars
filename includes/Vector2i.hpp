/*
 * Vector2i.hpp
 */

#ifndef VECTOR2I_HPP
#define VECTOR2I_HPP

#include <math.h>

class Vector2i {

public:
    Vector2i();
    Vector2i(int x, int y);
    ~Vector2i();

    double mag();
    void normalize();
    void mult(double n);

    void add(Vector2i *v);
    void sub(Vector2i *v);

    static Vector2i add(Vector2i *a, Vector2i *b);
    static Vector2i sub(Vector2i *a, Vector2i *b);
    static Vector2i mult(Vector2i *a, double n);

    int x;
    int y;

private:

};

#endif /* VECTOR2I_HPP */
