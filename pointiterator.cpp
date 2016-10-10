#include "pointiterator.h"

PointIterator::PointIterator(Mesh &m)
{
    v = m.getVertices();
    i = 0;
}

void PointIterator::reinit() {
    i = 0;
}

bool PointIterator::hasNext() {
    return (i < v->length());
}

Point PointIterator::next() {
    if (i >= v->length())
        throw "ERROR : NO MORE POINT";
    return (v->at(i++));
}

void PointIterator::goTo(int n) {
    if (n >= v->length())
        throw "ERROR : OUT OF BOUND";
    i = n;
}

Point PointIterator::first() {
    return v->at(0);
}

Point PointIterator::last() {
    return v->at(v->length()-1);
}
