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

    double x;
    double y;

private:

};

#endif /* MVECTOR_HPP */
