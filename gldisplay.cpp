#include "gldisplay.h"
#include <GL/gl.h>
#include <mesh.h>
#include <point.h>
#include <QVector>
#include <math.h>
#include <terrain.h>

#define FRUSTUM_SIZE 1.0f

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angle(0.0f),
    _angle2(240.0f)
{
    /*Mesh m = Mesh::makeCone(Point(0.0f,0.0f,-1.0f), 2.0f, 1.0f, 20);
    m.merge(Terrain(Point(-2.0f,-2.0f,-1.25f),Point(2.0f,2.0f,-1.25f),-0.1f,0.1f,50,50).toMesh());
    m.merge(Mesh::makeSphere(Point(0.0f,0.0f,1.0f), 0.5f, 20));
    m.merge(Mesh::makeCylinder(Point(0.0f,0.0f,-1.25f), 0.5f, 0.5f, 20));
    meshs.append(m);*/
    meshs.append(Mesh(":/mesh/queen.off"));
}

void GLDisplay::initializeGL()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);

    glVertex3f(1.0f,1.0f,1.0f);
    glVertex3f(1.0f,0.0f,1.0f);
    glVertex3f(1.0f,1.0f,0.0f);
    glEnd();
}

void drawMesh(Mesh m) {
    QVector<Point> points = m.getVertices();
    QVector<Triangle> triangles = m.getTriangles();
    float color = 0.0f;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < triangles.length(); i++) {
        glColor3f(1.0f, color, color);
        color = (color+1.0f/triangles.length());
        glVertex3f(points[triangles[i].x()].x(), points[triangles[i].x()].y(), points[triangles[i].x()].z());
        glVertex3f(points[triangles[i].y()].x(), points[triangles[i].y()].y(), points[triangles[i].y()].z());
        glVertex3f(points[triangles[i].z()].x(), points[triangles[i].z()].y(), points[triangles[i].z()].z());
    }
    glEnd();
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(_angle, 0.0f, 1.0f, 0.0f);
    glRotatef(_angle2, 1.0f, 0.0f, 0.0f);

    for (int i = 0; i < meshs.length(); i++) {
        drawMesh(meshs[i]);
    }
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

float min(float a, float b);

float max(float a, float b) {
    return (a > b) ? a : b;
}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if( event != NULL ) {
        QPoint position = event->pos();

        _angle += (position.x() - _position.x());
        _angle2 += position.y()-_position.y();


        _position = position;

        updateGL();
    }
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL )
        _position = event->pos();
}

void GLDisplay::keyPressEvent ( QKeyEvent * event ) {
    switch (event->key()) {
    case Qt::Key_Z :
        break;
    case Qt::Key_S :
        break;
    case Qt::Key_D :
        break;
    case Qt::Key_Q :
        break;
    default:
        break;
    }
}

