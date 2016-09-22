#ifndef TERRAIN_H
#define TERRAIN_H

#include <QVector>
#include "point.h"
#include "terrain.h"
#include <QImage>

class Terrain
{
public:
    Terrain(QImage img, Point a, Point b, float zMin, float zMax);
    Mesh toMesh();
    saveImg();

private:
    QVector<float> bedrock;
    QVector<float> soil;
    Point a;
    Point b;
    int width;
    int length;
};


#endif // TERRAIN_H
