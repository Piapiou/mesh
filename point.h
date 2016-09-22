#ifndef POINT_H
#define POINT_H

#include <QVector3D>

class Point : public QVector3D
{
public:
    Point();
    Point(const QVector3D p);
    Point(float x, float y, float z);

};

#endif // POINT_H
