#ifndef CANVASOPENGL_H
#define CANVASOPENGL_H

#include <QOpenGLWidget>
#include <QtGui>
#include <QWidget>
#include <vector>
#include <QMouseEvent>

using namespace std;


class CanvasOpenGL : public QOpenGLWidget {
public:
    CanvasOpenGL(QWidget *parent);
    ~CanvasOpenGL();
    void SetPointsColor(QColor color);
    void ClearScreen();

private:
    vector<QPoint> vertices;
    QColor pointsColor;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
};

#endif // CANVASOPENGL_H
