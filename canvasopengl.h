#ifndef CANVASOPENGL_H
#define CANVASOPENGL_H

#include <QOpenGLWidget>
#include <QtGui>
#include <QWidget>
#include <vector>
#include <QMouseEvent>

using namespace std;

#include "polygondrawer.h"

class CanvasOpenGL : public QOpenGLWidget {
public:
    CanvasOpenGL(QWidget *parent);
    ~CanvasOpenGL();
    void SetPointsColor(QColor color);
    void SetDrawer(PolygonDrawer* drawer);
    void ClearScreen();

private:
    vector<QPoint> vertices;
    QColor pointsColor;
    PolygonDrawer *drawer;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
};

#endif // CANVASOPENGL_H
