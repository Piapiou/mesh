#include "mesh.h"

class meshData : public QSharedData
{
public:

};

mesh::mesh()
{
    vertices = QVector<QVector3D>();
    triangles = QVector<QVector3D>();
}

mesh::mesh(const mesh &rhs)
{

}

mesh &mesh::operator=(const mesh &rhs)
{

}

mesh::~mesh()
{

}

