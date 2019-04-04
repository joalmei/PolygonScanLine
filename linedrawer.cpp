#include "linedrawer.h"
#include "canvasopengl.h"

LineDrawer::~LineDrawer() { }

void LineDrawer::Draw(CanvasOpenGL* canvas, QColor pointsColor) {
    QPainter painter(canvas);

    QPen myPen(1); // 1 px
    myPen.setColor(pointsColor);
    QBrush brush;
    brush.setColor(pointsColor);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(myPen);
    painter.setBrush(brush);

    painter.drawLine(*Points.first, *Points.second);
}
