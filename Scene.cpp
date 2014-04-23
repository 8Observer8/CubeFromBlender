#include "Scene.h"
#include <QtGui>

Scene::Scene( QWidget* pwgt/*= 0*/ ) :
    QGLWidget(pwgt),
    m_xRot(-90),
    m_yRot(0),
    m_zRot(0),
    m_nSca(1) {
}

void Scene::setPointsAndIndexes(QList<QVector3D> &points, QList<QVector3D> &indexes)
{
    const int elmToItem = 3;

    m_vertexArray.resize( points.size() * elmToItem );
    m_colorArray.resize( points.size() * elmToItem );
    m_indexArray.resize( indexes.size() * elmToItem );

    // Points
    for( int i = 0; i < points.size(); i++ )
    {
        const int idx = i * elmToItem;
        m_vertexArray[ idx + 0 ] = points[ i ].x();
        m_vertexArray[ idx + 1 ] = points[ i ].y();
        m_vertexArray[ idx + 2 ] = points[ i ].z();

        m_colorArray[ idx + 0 ] = 1. / (i+1);
        m_colorArray[ idx + 1 ] = 1. / (i+1);
        m_colorArray[ idx + 2 ] = 1. / (i+1);
    }

    // Indexes
    for( int i = 0; i < indexes.size(); i++ )
    {
        const int idx = i * elmToItem;
        m_indexArray[ idx + 0 ] = GLubyte( indexes[ i ].x() ) - 1;
        m_indexArray[ idx + 1 ] = GLubyte( indexes[ i ].y() ) - 1;
        m_indexArray[ idx + 2 ] = GLubyte( indexes[ i ].z() ) - 1;
    }

//    qDebug() << m_vertexArray;
//    qDebug() << m_indexArray;

    updateGL();
}

void Scene::initializeGL()
{
    qglClearColor(Qt::white); // цвет для очистки буфера изображения - будет просто фон окна
    glEnable(GL_DEPTH_TEST); // устанавливает режим проверки глубины пикселей
    glShadeModel(GL_FLAT); // отключает режим сглаживания цветов
    glEnable(GL_CULL_FACE); // устанавливаем режим, когда строятся только внешние поверхности

    //    getVertexArray(); // определить массив вершин
    //    getColorArray();  // определить массив цветов вершин
    //    getIndexArray();  // определить массив индексов вершин

    glEnableClientState(GL_VERTEX_ARRAY); // активизация массива вершин
    glEnableClientState(GL_COLOR_ARRAY);  // активизация массива цветов вершин
}

void Scene::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION); // устанавливает текущей проекционную матрицу
    glLoadIdentity(); // присваивает проекционной матрице единичную матрицу

    // отношение высоты окна виджета к его ширине
    GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;

    // мировое окно
    if ( nWidth >= nHeight ) {
        // параметры видимости ортогональной проекции
        glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
    } else {
        // плоскости отсечения (левая, правая, верхняя, нижняя, передняя, задняя)
        glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);
    }

    // параметры видимости перспективной проекции
    // glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
    // плоскости отсечения (левая, правая, верхняя, нижняя, ближняя, дальняя)

    // поле просмотра
    glViewport( 0, 0, ( GLint ) nWidth, ( GLint ) nHeight );
}

void Scene::paintGL()
{
    // glClear(GL_COLOR_BUFFER_BIT); // окно виджета очищается текущим цветом очистки
    // очистка буфера изображения и глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // устанавливаем положение и ориентацию матрице моделирования
    glMatrixMode(GL_MODELVIEW);
    // загружаем единичную матрицу моделирования
    glLoadIdentity();

    // последовательные преобразования
    glScalef(m_nSca, m_nSca, m_nSca); // масштабирование
    glRotatef(m_xRot, 1.0f, 0.0f, 0.0f); // поворот вокруг оси X
    glRotatef(m_yRot, 0.0f, 1.0f, 0.0f); // поворот вокруг оси Y
    glRotatef(m_zRot, 0.0f, 0.0f, 1.0f); // поворот вокруг оси Z

    // рисование осей координат
    drawAxis();

    // нарисовать фигуру
    //if ( m_sizeOfpointsArray != 0 ) {
        draw();
    //}
}

void Scene::mousePressEvent(QMouseEvent *pe)
{
    // при нажатии пользователем кнопки мыши переменной ptrMousePosition
    // будет присвоена координата указателя мыши
    m_mousePosition = pe->pos();

    // ptrMousePosition = (*pe).pos(); // можно и так написать
}

void Scene::mouseMoveEvent(QMouseEvent *pe)
{
    // вычисление углов поворота
    m_xRot += 180/m_nSca*(GLfloat)(pe->y()-m_mousePosition.y())/height();
    m_zRot += 180/m_nSca*(GLfloat)(pe->x()-m_mousePosition.x())/width();

    m_mousePosition = pe->pos();

    updateGL(); // обновление изображения
}

void Scene::wheelEvent(QWheelEvent *pe)
{
    if ((pe->delta()) > 0) {
        scalePlus();
    } else if ((pe->delta()) < 0) {
        scaleMinus();
    }

    updateGL();
}

void Scene::scalePlus() {
    m_nSca = m_nSca*1.1;
}

void Scene::scaleMinus() {
    m_nSca = m_nSca/1.1;
}

void Scene::drawAxis()
{
    // устанавливаем ширину линии приближенно в пикселях
    glLineWidth(3.0f);
    // до вызова команды ширина равна 1 пикселю по умолчанию

    // ось x красного цвета
    // устанавливаем цвет последующих примитивов
    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    glBegin(GL_LINES); // построение линии
    glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
    glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
    glEnd();

    // ось y зеленого цвета
    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 0.0f, -1.0f,  0.0f);

    // ось z синего цвета
    glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
    glVertex3f( 0.0f,  0.0f,  1.0f);
    glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();
}

void Scene::draw()
{
    // указываем, откуда нужно извлечь данные о массиве вершин
    glVertexPointer(3, GL_FLOAT, 0, m_vertexArray.constData());
    // указываем, откуда нужно извлечь данные о массиве цветов вершин
    glColorPointer(3, GL_FLOAT, 0, m_colorArray.constData());
    // используя массивы вершин и индексов, строим поверхности
    glDrawElements(GL_TRIANGLES, m_indexArray.size(), GL_UNSIGNED_BYTE, m_indexArray.constData());
}
