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
    vector<function<void(QMouseEvent*)>> OnMousePressed;
    vector<function<void(QMouseEvent*)>> OnMouseMoved;

public:
    CanvasOpenGL(QWidget* parent);
    ~CanvasOpenGL();

    void SetPointsColor(QColor);
    void AddDrawer(Drawer*);
    void ClearScreen();

private:
    QColor pointsColor;
    vector<Drawer*> drawers;

protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif // CANVASOPENGL_H
