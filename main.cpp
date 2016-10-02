#include "mainwindow.h"
#include <QApplication>
#include "gldisplay.h"
#include "mesh.h"
#include "terrain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
//    Mesh m = Terrain(Point(-2000.0f,-2000.0f,0.0f),Point(2000.0f,2000.0f,0.0f),-200.0f,200.0f,1024,1024).toMesh();
//    m.toOBJ("C:/Users/toshiba/Desktop/test.obj");

//    return 0;
}
