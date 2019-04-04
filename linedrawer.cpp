#include "linedrawer.h"
#include "canvasopengl.h"

LineDrawer::~LineDrawer() { }

void LineDrawer::Draw(CanvasOpenGL* canvas, QColor pointsColor) {
    //create a QPainter and pass a pointer to the device.
    //A paint device can be a QWidget, a QPixmap or a QImage
    QPainter painter(canvas);

    QPen myPen(1); // 1 px
    myPen.setColor(pointsColor);
    QBrush brush;
    brush.setColor(pointsColor);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(myPen);
    painter.setBrush(brush);

    painter.drawLine(Points.first, Points.second);
}
