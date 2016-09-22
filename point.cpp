#include "point.h"

Point::Point(){

}

Point::Point(const QVector3D p) {
    setX(p.x());
    setY(p.y());
    setZ(p.z());
}

Point::Point(float x, float y, float z) {
    setX(x);
    setY(y);
    setZ(z);
}
