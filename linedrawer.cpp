#include "linedrawer.h"
#include "canvasopengl.h"


// ==================================================================================================
LineDrawer::LineDrawer(CanvasOpenGL* canvas) : Drawer(canvas) { }

// ==================================================================================================
LineDrawer::~LineDrawer() { }

// ==================================================================================================
void LineDrawer::Draw(QColor pointsColor) {
    QPainter painter(canvas);

    QPen myPen(pointsColor);
    QBrush brush(pointsColor, Qt::SolidPattern);

    painter.setPen(myPen);
    painter.setBrush(brush);

    painter.drawLine(*Points.first, *Points.second);
}
