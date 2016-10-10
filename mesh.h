#ifndef MESH_H
#define MESH_H

#include <QMainWindow>
#include <QObject>
#include <QVector>
#include "point.h"
#include <QMatrix4x4>
#include "triangle.h"
#include <QSharedDataPointer>
#include <QWidget>

class Mesh
{
public:
    Mesh();
    Mesh(const Mesh &);
    Mesh(QString fileName);
    static Mesh makeBox(const Point p1, const Point p2);
    static Mesh makeSphere(const Point center, float rayon, int pointByArc);
    static Mesh makeCylinder(const Point center, float height, float rayon, int pointByArc);
    static Mesh makeCone(const Point center, float height, float rayon, int pointByArc);
    static Mesh makePlanFromTxt(const QString fileName);
    Mesh operator=(const Mesh &);
    Point getMiddle();
    ~Mesh();
    QVector<Point> * getVertices();
    QVector<Triangle> * getTriangles();
    void addVertice(Point v);
    void addTriangle(Triangle t);
    float distance(const Point p);
    void translate(const Point v);
    void rotate(const QMatrix4x4 m);
    void scale(float scale);
    void scale(const Point scale);
    void merge(Mesh m);
    void setAdjTri();
    void removePoint(int i);
    void removeTriangle(int i);
    void toOBJ(QString filePath);

private:
    QVector<Point> vertices;
    QVector<Triangle> triangles;
};

#endif // MESH_H
