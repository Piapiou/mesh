#ifndef POINTCIRCULATOR_H
#define POINTCIRCULATOR_H

#include <mesh.h>
#include <Point.h>
#include <QVector>

class PointCirculator
{
public:
    PointCirculator(Mesh &m, int sommet);
    void reinit();
    bool hasNext();
    int next();
    void goTo(int n);
    int first();
    int last();
    int length();

private:
    QVector<int> v;
    int i;
};

#endif // POINTCIRCULATOR_H
