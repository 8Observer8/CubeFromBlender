#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T21:00:14
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CubeFromBlender
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Parser.cpp \
    Scene.cpp

HEADERS  += MainWindow.h \
    FileError.h \
    FileOpenError.h \
    FileReadError.h \
    Parser.h \
    Scene.h \
    LogicError.h \
    EmptyInput.h \
    BadLine.h

FORMS    += MainWindow.ui
