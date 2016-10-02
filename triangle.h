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
    void setAdj1(int i);
    void setAdj2(int i);
    void setAdj3(int i);
    int getAdj(int nt);
private:
    int p1, p2, p3;
    int adj1, adj2, adj3;
};

#endif // TRIANGLE_H
