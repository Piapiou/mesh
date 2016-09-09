#ifndef MESH_H
#define MESH_H

#include <QMainWindow>
#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QSharedDataPointer>
#include <QWidget>

class meshData;

class mesh
{
public:
    mesh();
    mesh(const mesh &);
    mesh &operator=(const mesh &);
    ~mesh();

private:
    QVector<QVector3D> vertices;
    QVector<QVector3D> triangles;
};

#endif // MESH_H
