#ifndef ITERATEURTRIANGLE_H
#define ITERATEURTRIANGLE_H

#include <mesh.h>
#include <triangle.h>
#include <QVector>

class IterateurTriangle
{
public:
    IterateurTriangle(Mesh m);
    void reinit();
    bool hasNext();
    Triangle next();
    void goTo(int n);
    int first();
    int last();

private:
    QVector<Triangle> v;
    int i;

};

#endif // ITERATEURTRIANGLE_H
