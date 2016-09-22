#ifndef TERRAIN_H
#define TERRAIN_H

#include <QVector>
#include "point.h"

class Terrain
{
public:
    Terrain();

private:
    QVector<float> points;
    Point p1;
    Point p2;
    int width;
    int length;
};


#endif // TERRAIN_H
