#ifndef PointIterator_H
#define PointIterator_H

#include <mesh.h>
#include <Point.h>
#include <QVector>

class PointIterator
{
public:
    PointIterator(Mesh &m);
    void reinit();
    bool hasNext();
    Point next();
    void goTo(int n);
    Point first();
    Point last();

private:
    QVector<Point> * v;
    int i;

};

#endif // PointIterator_H
