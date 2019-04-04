#ifndef CANVASOPENGL_H
#define CANVASOPENGL_H

#include <QOpenGLWidget>
#include <QtGui>
#include <QWidget>
#include <vector>
#include <QMouseEvent>

using namespace std;

#include "drawer.h"

class CanvasOpenGL : public QOpenGLWidget {
public:
    vector<function<void(QMouseEvent *event)>> OnMousePressed;

public:
    CanvasOpenGL(QWidget *parent);
    ~CanvasOpenGL();

    void SetPointsColor(QColor color);
    void AddDrawer(Drawer* drawer);
    void ClearScreen();

private:
    QColor pointsColor;
    vector<Drawer*> drawers;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
};

#endif // CANVASOPENGL_H
