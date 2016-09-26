#include "triangle.h"

Triangle::Triangle() {
    p1 = 0;
    p2 = 0;
    p3 = 0;
}

Triangle::Triangle(int i1, int i2, int i3)
{
    p1 = i1;
    p2 = i2;
    p3 = i3;
}

int Triangle::x() {
    return p1;
}

int Triangle::y() {
    return p2;
}

int Triangle::z() {
    return p3;
}

Triangle Triangle::operator =(Triangle t) {
    return Triangle(t.x(), t.y(), t.z());
}
