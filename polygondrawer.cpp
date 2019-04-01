#include "polygondrawer.h"
#include "canvasopengl.h"

PolygonDrawer::PolygonDrawer() {

}

void PolygonDrawer::Draw(CanvasOpenGL*canvas, std::vector<QPoint>& vertices, QColor pointsColor) {
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

    for (std::vector<QPoint>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        painter.drawPoint(*i);
    }

    painter.drawPolygon(vertices.data(), vertices.size(), Qt::OddEvenFill);

    /* EXAMPLE OF A WHITE SQUARE WITH SIZE 100 X 100
    for (int i = 100; i <= 200; i++) {
        for(int j = 100; j <= 200; j++) {
            painter.drawPoint(i, j);
        }
    }
    */
}
