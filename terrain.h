#ifndef TERRAIN_H
#define TERRAIN_H

#include <QVector>
#include "point.h"
#include "mesh.h"
#include <QImage>

class Terrain
{
public:
    Terrain(const Point p1, const Point p2, float zMin, float zMax, int length, int width);
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
