#include "canvasopengl.h"


// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
CanvasOpenGL::CanvasOpenGL(QWidget *parent) : QOpenGLWidget(parent), pointsColor(255,255,255) {}

// ==================================================================================================
CanvasOpenGL::~CanvasOpenGL() {}

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
    for (auto drawer : drawers)
        drawer->Draw(this, vertices, pointsColor);
}

// ==================================================================================================
void CanvasOpenGL::resizeGL(int w, int h) {}

// ==================================================================================================
void CanvasOpenGL::mousePressEvent(QMouseEvent *event) {
    this->vertices.push_back(event->pos());

    this->update();
}
