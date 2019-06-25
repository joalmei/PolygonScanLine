#include "canvasopengl.h"
#include <QtMath>


// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
CanvasOpenGL::CanvasOpenGL(QWidget *parent) : QOpenGLWidget(parent), pointsColor(255,255,255) {
    setMouseTracking(true);
}

// ==================================================================================================
CanvasOpenGL::~CanvasOpenGL() {
}

// ==================================================================================================
void CanvasOpenGL::SetPointsColor(QColor color) {
    pointsColor.setRgb(color.rgb());
    this->update();
}

// ==================================================================================================
void CanvasOpenGL::AddDrawer(Drawer* drawer) {
    this->drawers.push_back(drawer);
}

// ==================================================================================================
void CanvasOpenGL::ClearScreen() {
    drawers.clear();
    this->update();
}

// ==================================================================================================
// PROTECTED MEMBERS
// ==================================================================================================
void CanvasOpenGL::initializeGL() {}

// ==================================================================================================
void CanvasOpenGL::paintGL() {
    for (auto drawer : drawers)
        drawer->Draw(pointsColor);
}

// ==================================================================================================
void CanvasOpenGL::resizeGL(int w, int h) { }

// ==================================================================================================
void CanvasOpenGL::mousePressEvent(QMouseEvent *event) {
    for(auto action : OnMousePressed)
        action(event);
    this->update();
}

// ==================================================================================================
void CanvasOpenGL::mouseMoveEvent(QMouseEvent *event) {
    for(auto action : OnMouseMoved)
        action(event);
    this->update();
}

// ==================================================================================================
void CanvasOpenGL::mouseDoubleClickEvent(QMouseEvent*) {

}

// ==================================================================================================
void CanvasOpenGL::mouseReleaseEvent(QMouseEvent *event) {
    for(auto action : OnMouseReleased)
        action(event);
    this->update();
}
