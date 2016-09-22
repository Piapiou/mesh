#include "gldisplay.h"
#include <GL/gl.h>
#include <mesh.h>
#include <point.h>
#include <QVector>

#define FRUSTUM_SIZE 1.0f

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angle(0.0f)
{
    printf("WTF ??");
}

void GLDisplay::initializeGL()
{
    printf("TEST");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0, 1.0, 0.0);

    meshs.append(Mesh::makeSphere(Point(0.0f, 0.0f, 0.0f), 1.0f, 20));

}

void drawMesh(Mesh m) {
    QVector<Point> points = m.getVertices();
    QVector<Point> triangles = m.getTriangles();

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < triangles.length(); i++) {
        glVertex3f(points[triangles[i].x()].x(), points[triangles[i].x()].z(), points[triangles[i].x()].z());
        glVertex3f(points[triangles[i].y()].x(), points[triangles[i].y()].z(), points[triangles[i].y()].z());
        glVertex3f(points[triangles[i].x()].z(), points[triangles[i].z()].z(), points[triangles[i].z()].z());
    }
    glEnd();
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(_angle, 0.0f, 1.0f, 0.0f);

    for (int i = 0; i < meshs.length(); i++)
        drawMesh(meshs[i]);
}

void GLDisplay::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glOrtho(-FRUSTUM_SIZE, FRUSTUM_SIZE,
            -FRUSTUM_SIZE, FRUSTUM_SIZE,
            -FRUSTUM_SIZE, FRUSTUM_SIZE);

    glMatrixMode(GL_MODELVIEW);

}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if( event != NULL ) {
        QPoint position = event->pos();

        _angle += (position.x() - _position.x());

        _position = position;

        updateGL();
    }
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL )
        _position = event->pos();
}
