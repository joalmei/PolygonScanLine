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
void CanvasOpenGL::setvMax (GLdouble arg1) {
    this->vMax = arg1;
    this->update();
}

void CanvasOpenGL::setvMin (GLdouble arg1) {
    this->vMin = arg1;
    this->update();
}

void CanvasOpenGL::sethMax (GLdouble arg1) {
    this->hMax = arg1;
    this->update();
}

void CanvasOpenGL::sethMin (GLdouble arg1) {
    this->hMin = arg1;
    this->update();
}

void CanvasOpenGL::setFar (GLdouble arg1) {
    this->farZ = arg1;
    this->update();
}

void CanvasOpenGL::setNear (GLdouble arg1) {
    this->nearZ = arg1;
    this->update();
}

void CanvasOpenGL::setxRot(GLdouble rot) {
    this->xRot = rot;
    this->update();
}

void CanvasOpenGL::setyRot(GLdouble rot) {
    this->yRot = rot;
    this->update();
}

void CanvasOpenGL::setzRot(GLdouble rot) {
    this->zRot = rot;
    this->update();
}

void CanvasOpenGL::setFovY (GLdouble arg1) {
    this->fovY = arg1;
    this->update();
}

void CanvasOpenGL::toggleProjection() {
    this->isPerspective = !this->isPerspective;
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


// =======================================================================================
// PRIVATE METHODS - VIEWING
// =======================================================================================
void CanvasOpenGL::setParameters() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (this->isPerspective) {
        this->perspectiveGL();
    } else {
        glOrtho(
            this->hMin,
            this->hMax,
            this->vMin,
            this->vMax,
            this->nearZ,
            this->farZ
        );
    }
}

void CanvasOpenGL::perspectiveGL() {
    GLdouble fW, fH;

    fH = tan(this->fovY / 360.0 * M_PI) * this->nearZ;
    fW = fH * this->aspect;

    glFrustum(-fW, fW, -fH, fH, this->nearZ, this->farZ);
}

// =======================================================================================
// PRIVATE METHODS - OBSERVER
// =======================================================================================
void CanvasOpenGL::LookAt() {
    // TODO
}
