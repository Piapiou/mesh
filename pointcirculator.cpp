#include "pointcirculator.h"
#include "triangleiterator.h"
#include "triangle.h"

PointCirculator::PointCirculator(Mesh &m, int sommet)
{
    m.setAdjTri();
    i = 0;
    QVector<Triangle> * tri = m.getTriangles();
    TriangleIterator triangles = TriangleIterator(m);
    while (triangles.hasNext()) {
        Triangle t = triangles.next();
        if (t.x() == sommet || t.y() == sommet || t.z() == sommet) {
            v = QVector<int>();
            int firstT;
            int p2;
            if (t.x() == sommet) {
                firstT = t.getAdj(3);
                p2 = t.y();
            } else if (t.y() == sommet) {
                firstT = t.getAdj(1);
                p2 = t.z();
            } else {
                firstT = t.getAdj(2);
                p2 = t.x();
            }
            int actualT = firstT;
            do {
                v.append(p2);
                Triangle ta = tri->at(actualT);

                if (ta.x() == sommet) {
                    actualT = ta.getAdj(3);
                    p2 = ta.y();
                } else if (ta.y() == sommet) {
                    actualT = ta.getAdj(1);
                    p2 = ta.z();
                } else {
                    actualT = ta.getAdj(2);
                    p2 = ta.x();
                }
            } while (actualT != firstT);
            break;
        }
    }
}

void PointCirculator::reinit() {
    i = 0;
}

bool PointCirculator::hasNext() {
    return (i < v.length());
}

int PointCirculator::next() {
    if (i >= v.length())
        throw "ERROR : NO MORE POINT";
    return (v[i++]);
}

void PointCirculator::goTo(int n) {
    if (n >= v.length())
        throw "ERROR : OUT OF BOUND";
    i = n;
}

int PointCirculator::first() {
    return v[0];
}

int PointCirculator::last() {
    return v[v.length()-1];
}

int PointCirculator::length() {
    return v.length();
}
