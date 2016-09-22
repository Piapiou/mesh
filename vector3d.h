#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "point.h"

class Vector3D
{
public:
    Vector3D(const Point p1, const Point p2);
    Point getP1();
    Point getP2();
    setP1(const Point p);
    setP2(const Point p);

private:
    Point p1;
    Point p2;
};

#endif // VECTOR3D_H
