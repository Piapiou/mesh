#include "triangleiterator.h"

TriangleIterator::TriangleIterator(Mesh &m)
{
    v = m.getTriangles();
    i = 0;
}

void TriangleIterator::reinit() {
    i = 0;
}

bool TriangleIterator::hasNext() {
    return (i < v->length());
}

Triangle TriangleIterator::next() {
    if (i >= v->length())
        throw "ERROR : NO MORE TRIANGLE";
    return (v->at(i++));
}

void TriangleIterator::goTo(int n) {
    if (n >= v->length())
        throw "ERROR : OUT OF BOUND";
    i = n;
}

Triangle TriangleIterator::first() {
    return v->at(0);
}

Triangle TriangleIterator::last() {
    return v->at(v->length()-1);
}
