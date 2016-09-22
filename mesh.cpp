#include "mesh.h"
#include <math.h>
#include <limits>

#define PI 3.14159265


Mesh::Mesh()
{
    vertices = QVector<Point>();
    triangles = QVector<Point>();
}

Mesh::Mesh(const Mesh &rhs)
{
    vertices = QVector<Point>(rhs.vertices);
    triangles = QVector<Point>(rhs.triangles);
}

Mesh Mesh::makeBox(const Point p1, const Point p2) {

    Mesh m = Mesh();
    m.vertices.append(Point(p1));
    m.vertices.append(Point(p1.x(), p1.y(), p2.z()));
    m.vertices.append(Point(p1.x(), p2.y(), p1.z()));
    m.vertices.append(Point(p1.x(), p2.y(), p2.z()));
    m.vertices.append(Point(p2.x(), p1.y(), p2.z()));
    m.vertices.append(Point(p2.x(), p2.y(), p1.z()));
    m.vertices.append(Point(p2.x(), p2.y(), p2.z()));
    m.vertices.append(Point(p2));

    m.triangles.append(Point(0,3,1));
    m.triangles.append(Point(0,2,3));
    m.triangles.append(Point(2,7,3));
    m.triangles.append(Point(2,6,7));
    m.triangles.append(Point(0,6,2));
    m.triangles.append(Point(0,4,6));
    m.triangles.append(Point(3,5,1));
    m.triangles.append(Point(3,7,5));
    m.triangles.append(Point(6,5,7));
    m.triangles.append(Point(6,4,5));
    m.triangles.append(Point(4,1,5));
    m.triangles.append(Point(4,0,1));

    return m;
}

Mesh Mesh::makeSphere(const Point center, float rayon, int pointByArc) {
    Mesh m = Mesh();
    float step = PI/pointByArc;
    float is = -PI/2;
    float ib = -PI;


    int PreviousSmallLoop = 0;
    int PreviousBigLoop = 0;

    m.vertices.append(Point(rayon*cos(is)*cos(ib)+center.x(),
                              rayon*cos(is)*sin(ib)+center.y(),
                              rayon*sin(ib)+center.z()));

    for(is = -PI/2+step; is < PI/2; is += step) {
        m.vertices.append(Point(rayon*cos(is)*cos(ib)+center.x(),
                                  rayon*cos(is)*sin(ib)+center.y(),
                                  rayon*sin(ib)+center.z()));
        PreviousSmallLoop++;
    }


    for (ib = -PI+step; ib < PI; ib += step) {

        m.vertices.append(Point(rayon*cos(is)*cos(ib)+center.x(),
                                  rayon*cos(is)*sin(ib)+center.y(),
                                  rayon*sin(ib)+center.z()));
        PreviousSmallLoop++;

        for(is = -PI/2+step; is < PI/2; is += step) {
            m.vertices.append(Point(rayon*cos(is)*cos(ib)+center.x(),
                                      rayon*cos(is)*sin(ib)+center.y(),
                                      rayon*sin(ib)+center.z()));

            m.triangles.append(Point(PreviousBigLoop, PreviousBigLoop+1, PreviousSmallLoop));
            m.triangles.append(Point(PreviousBigLoop, PreviousSmallLoop, PreviousSmallLoop+1));

            PreviousSmallLoop++;
            PreviousBigLoop++;
        }
        PreviousBigLoop++;
    }

    PreviousSmallLoop = 0;

    for(is = -PI/2+step; is < PI/2; is += step) {
        m.vertices.append(Point(rayon*cos(is)*cos(ib)+center.x(),
                                  rayon*cos(is)*sin(ib)+center.y(),
                                  rayon*sin(ib)+center.z()));

        m.triangles.append(Point(PreviousBigLoop, PreviousBigLoop+1, PreviousSmallLoop));
        m.triangles.append(Point(PreviousBigLoop, PreviousSmallLoop, PreviousSmallLoop+1));

        PreviousSmallLoop++;
        PreviousBigLoop++;
    }

    return m;
}

Mesh Mesh::operator=(const Mesh &rhs)
{    
    Mesh m = Mesh();
    m.vertices = QVector<Point>(rhs.vertices);
    m.triangles = QVector<Point>(rhs.triangles);
    return m;
}

Point Mesh::getMiddle() {
    float x = 0;
    float y = 0;
    float z = 0;
    for (int i = 0; i < vertices.length(); i++) {
        x += vertices[i].x(); y += vertices[i].y(); z += vertices[i].z();
    }

    return Point(x/vertices.length(),y/vertices.length(),z/vertices.length());
}


QVector<Point> Mesh::getVertices() {
    return vertices;
}

QVector<Point> Mesh::getTriangles() {
    return triangles;
}

float min(float a, float b) {
    return (b<a)?b:a;
}

float Mesh::distance(const Point p) {
    float result = std::numeric_limits<float>::max();
    for (int i = 0; i < vertices.length(); i++) {
        result = min(result, pow(p.x()-vertices[i].x(),2)+pow(p.y()-vertices[i].y(),2)+pow(p.z()-vertices[i].z(),2));
    }
    return sqrt(result);
}

void Mesh::scale(const Point scale) {
    const Point middle = getMiddle();

    for (int i = 0; i < vertices.length(); i++) {
       vertices[i].setX((vertices[i].x()-middle.x())*scale.x()+middle.x());
       vertices[i].setY((vertices[i].y()-middle.y())*scale.y()+middle.y());
       vertices[i].setZ((vertices[i].z()-middle.z())*scale.z()+middle.z());
    }
}

void Mesh::scale(float scale) {
    const Point middle = getMiddle();

    for (int i = 0; i < vertices.length(); i++) {
       vertices[i].setX((vertices[i].x()-middle.x())*scale+middle.x());
       vertices[i].setY((vertices[i].y()-middle.y())*scale+middle.y());
       vertices[i].setZ((vertices[i].z()-middle.z())*scale+middle.z());
    }
}

void Mesh::rotate(const QMatrix4x4 m) {
    const Point middle = getMiddle();

    for (int i = 0; i < vertices.length(); i++) {
       vertices[i].setX(vertices[i].x()-middle.x());
       vertices[i].setY(vertices[i].y()-middle.y());
       vertices[i].setZ(vertices[i].z()-middle.z());
       vertices[i] = Point(m * vertices[i]);
       vertices[i].setX(vertices[i].x()+middle.x());
       vertices[i].setY(vertices[i].y()+middle.y());
       vertices[i].setZ(vertices[i].z()+middle.z());
    }
}

void Mesh::translate(const Point v) {
    for (int i = 0; i < vertices.length(); i++) {
       vertices[i] += v;
    }
}

void Mesh::merge(const Mesh m) {
    int mLength = m.vertices.length();
    vertices.append(m.vertices);
    for (int i = 0; i < m.triangles.length(); i++) {
        triangles.append(Point(m.triangles[i].x()+mLength,m.triangles[i].y()+mLength,m.triangles[i].z()+mLength));
    }
}

Point Mesh::isInside(Vector3D v) {
    /*Point u = v.getP2() - v.getP1();
    Point w;
    float D, N;

    // TODO

    return Point();*/
}

Mesh::~Mesh()
{
    delete &vertices;
    delete &triangles;
}
