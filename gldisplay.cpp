#include "gldisplay.h"
#include <iterateurtriangle.h>
#include <GL/gl.h>
#include <mesh.h>
#include <point.h>
#include <QVector>
#include <math.h>
#include <terrain.h>
#include <time.h>

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angle(0.0f),
    _angle2(240.0f),
    _frustum_size(2.0f)
{
    Mesh m = Mesh::makeBox(Point(-1.0f,-1.0f,-1.0f), Point(1.0f,1.0f,1.0f));
    m.setAdjTri();

    QVector<Triangle> t = m.getTriangles();
    for (int i = 0; i < t.length(); i++) {
        printf("%d -> %d %d %d\n", i, t[i].getAdj(1), t[i].getAdj(2), t[i].getAdj(3));
    }

    //m.merge(Mesh::makeSphere(Point(0.0f,0.0f,1.0f), 0.5f, 20));
    //m.merge(Mesh::makeCylinder(Point(0.0f,0.0f,-1.25f), 0.5f, 0.5f, 20));

    //Mesh m = Mesh(":/mesh/queen.off");
    meshs.append(m);
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

float abs(float x) {
    return (x > 0) ? x : -x;
}

void drawMesh(Mesh m) {


    QVector<Point> points = m.getVertices();
    IterateurTriangle i = IterateurTriangle(m);

    glBegin(GL_TRIANGLES);
    while (i.hasNext()) {
        Triangle t = i.next();

        QVector3D ab = QVector3D(   points[t.y()].x()-points[t.x()].x(),
                                    points[t.y()].y()-points[t.x()].y(),
                                    points[t.y()].z()-points[t.x()].z());
        QVector3D ac = QVector3D(   points[t.z()].x()-points[t.x()].x(),
                                    points[t.z()].y()-points[t.x()].y(),
                                    points[t.z()].z()-points[t.x()].z());
        Point pv = Point(ab.y()*ac.z()-ab.z()*ac.y(),
                         ab.z()*ac.x()-ab.x()*ac.z(),
                         ab.x()*ac.y()-ab.y()*ac.x());
        float mult = (abs(pv.x()) > abs(pv.y())) ? ((abs(pv.x()) > abs(pv.z())) ? abs(pv.x()) : abs(pv.z())) : ((abs(pv.y()) > abs(pv.z())) ? abs(pv.y()) : abs(pv.z()));
        glColor3f(pv.x()/mult/2+0.5,pv.y()/mult/2+0.5,pv.z()/mult/2+0.5);
        glVertex3f(points[t.x()].x(), points[t.x()].y(), points[t.x()].z());
        glVertex3f(points[t.y()].x(), points[t.y()].y(), points[t.y()].z());
        glVertex3f(points[t.z()].x(), points[t.z()].y(), points[t.z()].z());
    }
    glEnd();

}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(_angle, 0.0f, 1.0f, 0.0f);
    glRotatef(_angle2, 1.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(1.0f,0.0f,0.0f);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,1.0f,0.0f);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,1.0f);
    glEnd();
    for (int i = 0; i < meshs.length(); i++) {
        drawMesh(meshs[i]);
    }
}


void GLDisplay::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glOrtho(-_frustum_size, _frustum_size,
            -_frustum_size, _frustum_size,
            -_frustum_size, _frustum_size);

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
    case Qt::Key_I : _frustum_size += 1.0f;
        break;
    case Qt::Key_J : _frustum_size -= 1.0f;
        break;
    }
    printf("PINGOUIN");
}

