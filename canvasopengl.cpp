#include "canvasopengl.h"

// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
CanvasOpenGL::CanvasOpenGL(QWidget *parent) : QOpenGLWidget(parent) , nextPointColor(255,255,255){}

// ==================================================================================================
CanvasOpenGL::~CanvasOpenGL() {}

// ==================================================================================================
void CanvasOpenGL::SetNextPointColor(QColor color) {
    nextPointColor = color;
}

// ==================================================================================================
void CanvasOpenGL::ClearScreen() {
    if(!this->vertices.empty()) {
        this->vertices.clear();
        this->update();
    }
}

// ==================================================================================================
// PROTECTED MEMBERS
// ==================================================================================================
void CanvasOpenGL::initializeGL() {}

// ==================================================================================================
void CanvasOpenGL::paintGL() {
    //create a QPainter and pass a pointer to the device.
    //A paint device can be a QWidget, a QPixmap or a QImage
    QPainter painter(this);

    QPen myPen(1); // 1 px
    myPen.setColor(nextPointColor);

    painter.setPen(myPen);

    for (vector<QPoint>::iterator i = this->vertices.begin(); i != this->vertices.end(); i++) {
        painter.drawPoint(*i);
    }

    /* EXAMPLE OF A WHITE SQUARE WITH SIZE 100 X 100
     * for (int i = 100; i <= 200; i++) {
        for(int j = 100; j <= 200; j++) {
            painter.drawPoint(i, j);
        }
    }*/
}

// ==================================================================================================
void CanvasOpenGL::resizeGL(int w, int h) {}

// ==================================================================================================
void CanvasOpenGL::mousePressEvent(QMouseEvent *event) {
    this->vertices.push_back(event->pos());

    this->update();
}
