#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
#include <mesh.h>
#include <QMouseEvent>
#include <QVector>

class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);

    virtual void initializeGL();

    virtual void paintGL();

    virtual void resizeGL(int w, int h);

protected:
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );

private:
    void drawSierpinski();

    float _angle2;
    float _angle;
    QPoint _position;
    QVector<Mesh> meshs;

signals:

public slots:

};

#endif // GLDISPLAY_H
