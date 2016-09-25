#ifndef MESH_H
#define MESH_H

#include <QMainWindow>
#include <QObject>
#include <QVector>
#include "point.h"
#include <QMatrix4x4>
#include "vector3d.h"
#include <QSharedDataPointer>
#include <QWidget>

class Mesh
{
public:
    Mesh();
    Mesh(const Mesh &);
    static Mesh makeBox(const Point p1, const Point p2);
    static Mesh makeSphere(const Point center, float rayon, int pointByArc);
    Mesh operator=(const Mesh &);
    Point getMiddle();
    ~Mesh();
    QVector<Point> getVertices();
    QVector<Point> getTriangles();
    addVertice(Point v);
    addTriangle(Point t);
    float distance(const Point p);
    void translate(const Point v);
    void rotate(const QMatrix4x4 m);
    void scale(float scale);
    void scale(const Point scale);
    void merge(const Mesh m);

private:
    QVector<Point> vertices;
    QVector<Point> triangles;
};

#endif // MESH_H
