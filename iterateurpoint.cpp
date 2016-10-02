#include "iterateurPoint.h"

IterateurPoint::IterateurPoint(Mesh m)
{
    v = QVector<Point>(m.getVertices());
    i = 0;
}

void IterateurPoint::reinit() {
    i = 0;
}

bool IterateurPoint::hasNext() {
    return (i < v.length());
}

Point IterateurPoint::next() {
    if (i >= v.length())
        throw "ERROR : NO MORE POINT";
    return (v[i++]);
}

void IterateurPoint::goTo(int n) {
    if (n >= v.length())
        throw "ERROR : OUT OF BOUND";
    i = n;
}

int IterateurPoint::first() {
    return 0;
}

int IterateurPoint::last() {
    return v.length()-1;
}
