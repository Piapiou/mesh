#ifndef TRIANGLECIRCULATOR_H
#define TRIANGLECIRCULATOR_H


#include <mesh.h>
#include <Triangle.h>
#include <QVector>

class TriangleCirculator
{
public:
    TriangleCirculator(Mesh &m, int sommet);
    void reinit();
    bool hasNext();
    int next();
    void goTo(int n);
    int first();
    int last();

private:
    QVector<int> v;
    int i;
};

#endif // TRIANGLECIRCULATOR_H
