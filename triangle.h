#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QVector3D>

class Triangle
{
public:
    Triangle();
    Triangle(int i1, int i2, int i3);
    int x();
    int y();
    int z();
    Triangle operator=(Triangle t);

private:
    int p1, p2, p3;

};

#endif // TRIANGLE_H
