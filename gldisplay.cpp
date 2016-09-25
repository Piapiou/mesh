#include "gldisplay.h"
#include <GL/gl.h>
#include <mesh.h>
#include <point.h>
#include <QVector>
#include <math.h>
#include <terrain.h>

#define FRUSTUM_SIZE 1.5f

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angle(0.0f),
    _angle2(0.0f)
{
    meshs.append(Terrain(Point(-1.0f,-1.0f,-1.0f), Point(1.0f,1.0f,-1.0f), -0.1f, 0.1f, 20, 20).toMesh());
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
    QVector<Point> triangles = m.getTriangles();
    float color = 0.0f;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < triangles.length(); i++) {
        glColor3f(1.0f, color, color);
        color = (color+1.0f/10);
        color = (color > 1.0f) ? color-1.0f : color;
        glVertex3f(points[(int)triangles[i].x()].x(), points[(int)triangles[i].x()].y(), points[(int)triangles[i].x()].z());
        glVertex3f(points[(int)triangles[i].y()].x(), points[(int)triangles[i].y()].y(), points[(int)triangles[i].y()].z());
        glVertex3f(points[(int)triangles[i].z()].x(), points[(int)triangles[i].z()].y(), points[(int)triangles[i].z()].z());
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
