#ifndef TriangleIterator_H
#define TriangleIterator_H

#include <mesh.h>
#include <triangle.h>
#include <QVector>

class TriangleIterator
{
public:
    TriangleIterator(Mesh &m);
    void reinit();
    bool hasNext();
    Triangle next();
    void goTo(int n);
    Triangle first();
    Triangle last();

private:
    QVector<Triangle> * v;
    int i;

};

#endif // TriangleIterator_H
