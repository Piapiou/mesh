#include "vector3d.h"

Vector3D::Vector3D(const Point p1, const Point p2) {
    this->p1 = Point(p1);
    this->p2 = Point(p2);
}

Point Vector3D::getP1() {
    return p1;
}

Point Vector3D::getP2() {
    return p2;
}

Vector3D::setP1(const Point p) {
    p1 = Point(p);
}

Vector3D::setP2(const Point p) {
    p2 = Point(p);
}
