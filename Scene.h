#ifndef SCENE_H
#define SCENE_H

#include <QGLWidget>
#include <QObject>
#include <memory>
#include <QList>
#include <QVector3D>

class Scene : public QGLWidget {
    Q_OBJECT
public:
    Scene( QWidget *pwgt = 0 );
    void setPointsAndIndexes( QList<QVector3D> &points, QList<QVector3D> &indexes );

protected:
    virtual void initializeGL();
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);
    virtual void wheelEvent(QWheelEvent* pe);
    void scalePlus();
    void scaleMinus();

private:
    void drawAxis(); // построить оси координат
    void draw();

private:
    GLfloat m_xRot; // переменная хранит угол поворота вокруг оси X
    GLfloat m_yRot; // переменная хранит угол поворота вокруг оси Y
    GLfloat m_zRot; // переменная хранит угол поворота вокруг оси Z
    GLfloat m_nSca; // переменная отвечает за масштабирование объекта

    QPoint m_mousePosition; // координата указателя мыши
    GLfloat **m_vertexArray;
    GLfloat **m_indexArray;
    GLfloat **m_colorArray;
    int m_sizeOfpointsArray;
    int m_sizeOfIndexesArray;
};

#endif // SCENE_H
