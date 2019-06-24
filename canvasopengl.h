#ifndef CANVASOPENGL_H
#define CANVASOPENGL_H

#include <QOpenGLWidget>
#include <QtGui>
#include <QWidget>
#include <vector>
#include <QMouseEvent>
#include <QtOpenGL>


using namespace std;

#include "drawer.h"

class CanvasOpenGL : public QOpenGLWidget {
public:
    vector<function<void(QMouseEvent*)>> OnMousePressed;
    vector<function<void(QMouseEvent*)>> OnMouseReleased;
    vector<function<void(QMouseEvent*)>> OnMouseMoved;

public:
    CanvasOpenGL(QWidget* parent);
    ~CanvasOpenGL();

    void SetPointsColor(QColor);
    void AddDrawer(Drawer*);
    void ClearScreen();


    void setvMax (GLdouble arg1);
    void setvMin (GLdouble arg1);
    void sethMax (GLdouble arg1);
    void sethMin (GLdouble arg1);
    void setFar (GLdouble arg1);
    void setNear (GLdouble arg1);

    void setxRot (GLdouble rot);
    void setyRot (GLdouble rot);
    void setzRot (GLdouble rot);

    void toggleProjection ();
    void setFovY(GLdouble arg1);

private:
    QColor pointsColor;
    vector<Drawer*> drawers;


    // VIEWING MEMBERS
    // GLint height, width;
    GLdouble
        hMin,   hMax,
        vMin,   vMax,
        nearZ,  farZ,
        aspect, fovY;
    GLboolean isPerspective;

    // VIEWING METHODS
    void setParameters();
    void perspectiveGL();

    // OBSERVER MEMBERS
    QVector3D *up, *eye, *center;
    GLdouble xRot, yRot, zRot;
    QPoint lastPos;

    // OBSERVER METHODS
    void LookAt();

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
