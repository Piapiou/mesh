#include "gldisplay.h"
#include <GL/gl.h>
#include <mesh.h>
#include <point.h>
#include <QVector>

#define FRUSTUM_SIZE 1.0f

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angle(0.0f),
    _angle2(0.0f)
{
    meshs.append(Mesh::makeBox(Point(-0.5f, -0.5f, -0.5f), Point(0.5f, 0.5f, 0.5f)));
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
        glColor3f(1.0, 1.0-color, color);
        color += 0.1f;
        glVertex3f(points[(int)triangles[i].x()].x(), points[(int)triangles[i].x()].y(), points[(int)triangles[i].x()].z());
        glVertex3f(points[(int)triangles[i].y()].x(), points[(int)triangles[i].y()].y(), points[(int)triangles[i].y()].z());
        glVertex3f(points[(int)triangles[i].z()].x(), points[(int)triangles[i].z()].y(), points[(int)triangles[i].z()].z());
        printf("(%f,%f,%f)",points[(int)triangles[i].x()].x(), points[(int)triangles[i].x()].y(), points[(int)triangles[i].x()].z());
        printf("(%f,%f,%f)",points[(int)triangles[i].y()].x(), points[(int)triangles[i].y()].y(), points[(int)triangles[i].y()].z());
        printf("(%f,%f,%f)",points[(int)triangles[i].z()].x(), points[(int)triangles[i].z()].y(), points[(int)triangles[i].z()].z());
        printf("\n");

    }
    printf("----\n");
    glEnd();
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(_angle, 0.0f, 1.0f-_angle2, _angle2);

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
        _angle2 += max(0,min(180,position.y()));


        _position = position;

        updateGL();
    }
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL )
        _position = event->pos();
}
