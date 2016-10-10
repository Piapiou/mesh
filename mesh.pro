#-------------------------------------------------
#
# Project created by QtCreator 2016-09-09T15:43:04
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = mesh
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mesh.cpp \
    vector3d.cpp \
    point.cpp \
    gldisplay.cpp \
    triangle.cpp \
    triangleiterator.cpp \
    pointiterator.cpp \
    pointcirculator.cpp \
    trianglecirculator.cpp

HEADERS  += mainwindow.h \
    mesh.h \
    vector3d.h \
    point.h \
    gldisplay.h \
    triangle.h \
    pointiterator.h \
    triangleiterator.h \
    pointcirculator.h \
    trianglecirculator.h


LIBS += -lopengl32

FORMS += \
    mainwindow.ui

RESOURCES += \
    rsc.qrc

DISTFILES +=
