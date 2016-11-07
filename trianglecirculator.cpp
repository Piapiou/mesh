#include "trianglecirculator.h"
#include "triangleiterator.h"

TriangleCirculator::TriangleCirculator(Mesh &m, int sommet)
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
                v.append(actualT);
                Triangle ta = tri->at(actualT);
                //printf("%d(%d,%d,%d) (%d,%d,%d)\n",actualT,ta.x(),ta.y(),ta.z(),ta.getAdj(1),ta.getAdj(2),ta.getAdj(3));
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

void TriangleCirculator::reinit() {
    i = 0;
}

bool TriangleCirculator::hasNext() {
    return (i < v.length());
}

int TriangleCirculator::next() {
    if (i >= v.length())
        throw "ERROR : NO MORE TRIANGLE";
    return (v[i++]);
}

void TriangleCirculator::goTo(int n) {
    if (n >= v.length())
        throw "ERROR : OUT OF BOUND";
    i = n;
}

int TriangleCirculator::first() {
    return v[0];
}

int TriangleCirculator::last() {
    return v[v.length()-1];
}
