#include "polygondrawer.h"
#include "canvasopengl.h"


// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
PolygonDrawer::PolygonDrawer() {}

// ==================================================================================================
PolygonDrawer::~PolygonDrawer() {}

// ==================================================================================================
void PolygonDrawer::Draw(CanvasOpenGL*canvas, QColor pointsColor) {
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

    // qt built-in method that implements the MidPointAlgorithm:
    painter.drawPolygon(Vertices.data(), Vertices.size(), Qt::OddEvenFill);
    // our method to implement:
    midPointMethod(Vertices, painter);
}

// ==================================================================================================
// PRIVATE MEMBERS
// ==================================================================================================
void PolygonDrawer::midPointMethod(std::vector<QPoint>& vertices, QPainter& painter) {
    for (std::vector<QPoint>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        painter.drawPoint(*i);
    }
    /* EXAMPLE OF A WHITE SQUARE WITH SIZE 100 X 100
    for (int i = 100; i <= 200; i++) {
        for(int j = 100; j <= 200; j++) {
            painter.drawPoint(i, j);
        }
    }
    */
}
