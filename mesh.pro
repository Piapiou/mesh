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
    terrain.cpp \
    gldisplay.cpp

HEADERS  += mainwindow.h \
    mesh.h \
    vector3d.h \
    point.h \
    terrain.h \
    gldisplay.h


LIBS += -lopengl32

FORMS += \
    mainwindow.ui
