#include "iterateurtriangle.h"

IterateurTriangle::IterateurTriangle(Mesh m)
{
    v = QVector<Triangle>(m.getTriangles());
    i = 0;
}

void IterateurTriangle::reinit() {
    i = 0;
}

bool IterateurTriangle::hasNext() {
    return (i < v.length());
}

Triangle IterateurTriangle::next() {
    if (i >= v.length())
        throw "ERROR : NO MORE TRIANGLE";
    return (v[i++]);
}

void IterateurTriangle::goTo(int n) {
    if (n >= v.length())
        throw "ERROR : OUT OF BOUND";
    i = n;
}

int IterateurTriangle::first() {
    return 0;
}

int IterateurTriangle::last() {
    return v.length()-1;
}
