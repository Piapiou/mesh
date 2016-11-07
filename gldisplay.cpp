#include "gldisplay.h"
#include <triangleiterator.h>
#include <trianglecirculator.h>
#include <pointiterator.h>
#include <pointcirculator.h>
#include <GL/gl.h>
#include <mesh.h>
#include <point.h>
#include <QVector>
#include <math.h>
#include <time.h>

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angle(0.0f),
    _angle2(240.0f),
    _frustum_size(3.0f)
{
    Mesh m = Mesh::makePlanFromTxt(":/other/points.txt");

    //m.merge(Mesh::makeSphere(Point(0.0f,0.0f,1.0f), 0.5f, 20));
    //m.merge(Mesh::makeCylinder(Point(0.0f,0.0f,-1.25f), 0.5f, 0.5f, 20));

    /*Mesh m = Mesh(":/mesh/queen.off");
    m.scale(2.5);*/
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

void drawMesh(Mesh &m) {


    QVector<Point> * points = m.getVertices();
    TriangleIterator i = TriangleIterator(m);
    float color = 0.25f;

    //glBegin(GL_TRIANGLES);
    while (i.hasNext()) {
        Triangle t = i.next();

        /*QVector3D ab = QVector3D(   points->at(t.y()).x()-points->at(t.x()).x(),
                                    points->at(t.y()).y()-points->at(t.x()).y(),
                                    points->at(t.y()).z()-points->at(t.x()).z());
        QVector3D ac = QVector3D(   points->at(t.z()).x()-points->at(t.x()).x(),
                                    points->at(t.z()).y()-points->at(t.x()).y(),
                                    points->at(t.z()).z()-points->at(t.x()).z());
        Point pv = Point(ab.y()*ac.z()-ab.z()*ac.y(),
                         ab.z()*ac.x()-ab.x()*ac.z(),
                         ab.x()*ac.y()-ab.y()*ac.x());
        float mult = (abs(pv.x()) > abs(pv.y())) ? ((abs(pv.x()) > abs(pv.z())) ? abs(pv.x()) : abs(pv.z())) : ((abs(pv.y()) > abs(pv.z())) ? abs(pv.y()) : abs(pv.z()));
        glColor3f(pv.y()/mult/2+0.5,pv.z()/mult/2+0.5,pv.x()/mult/2+0.5);*/
        //color = color + 0.025f;
        //glColor3f(color,color,color);
        glColor3f(0,255,0);
        glBegin(GL_LINE_LOOP);
        glVertex3f(points->at(t.x()).x(), points->at(t.x()).y(), points->at(t.x()).z());
        glVertex3f(points->at(t.y()).x(), points->at(t.y()).y(), points->at(t.y()).z());
        glVertex3f(points->at(t.z()).x(), points->at(t.z()).y(), points->at(t.z()).z());
        glEnd();
    }

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
        if (event->buttons() & Qt::LeftButton) {
            _angle += (position.x() - _position.x());
            _angle2 += position.y()-_position.y();
        } else {
            _frustum_size += (position.x() - _position.x());
        }
        _position = position;

        updateGL();
    }
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL )
        _position = event->pos();
    printf("MousePressEvent\n");
}

void GLDisplay::keyPressEvent ( QKeyEvent * event ) {
    switch (event->key()) {
    case Qt::Key_I :
        break;
    case Qt::Key_J :
        break;
    }
    printf("KeyPressEvent\n");
}

