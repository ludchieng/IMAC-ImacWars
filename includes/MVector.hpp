/*
 * MVector.hpp
 */

#ifndef MVECTOR_HPP
#define MVECTOR_HPP

#include <math.h>

class MVector {

public:
    MVector();
    MVector(double x, double y);
    ~MVector();

    double mag();
    void normalize();
    void mult(double n);

    void add(MVector *v);
    void sub(MVector *v);

    static MVector add(MVector *a, MVector *b);
    static MVector sub(MVector *a, MVector *b);

    double x;
    double y;

private:

};

#endif /* MVECTOR_HPP */
