#ifndef ITERATEURPOINT_H
#define ITERATEURPOINT_H

#include <mesh.h>
#include <Point.h>
#include <QVector>

class IterateurPoint
{
public:
    IterateurPoint(Mesh m);
    void reinit();
    bool hasNext();
    Point next();
    void goTo(int n);
    int first();
    int last();

private:
    QVector<Point> v;
    int i;

};

#endif // ITERATEURPOINT_H
