#include "polygondrawer.h"
#include "canvasopengl.h"


// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
PolygonDrawer::PolygonDrawer(CanvasOpenGL* canvas) : Drawer(canvas) { }

// ==================================================================================================
PolygonDrawer::~PolygonDrawer() {}

// ==================================================================================================
void PolygonDrawer::Draw(QColor pointsColor) {
    //create a QPainter and pass a pointer to the device.
    //A paint device can be a QWidget, a QPixmap or a QImage
    QPainter painter(canvas);

    QPen myPen(pointsColor);
    QBrush brush(pointsColor, Qt::SolidPattern);

    painter.setPen(myPen);
    painter.setBrush(brush);

    // qt built-in method that implements the MidPointAlgorithm:
    vector<QPoint> points;
    points.reserve(Vertices.size());
    for(auto vertex : Vertices)
        points.push_back(*vertex);
    painter.drawPolygon(points.data(), points.size(), Qt::OddEvenFill);
    // our method to implement:
    midPointMethod(Vertices, painter);
}

// ==================================================================================================
// PRIVATE MEMBERS
// ==================================================================================================
void PolygonDrawer::midPointMethod(std::vector<QPoint*>& vertices, QPainter& painter) {
    for (auto i = vertices.begin(); i != vertices.end(); i++) {
        painter.drawPoint(**i);
    }

    /* EXAMPLE OF A WHITE SQUARE WITH SIZE 100 X 100
    for (int i = 100; i <= 200; i++) {
        for(int j = 100; j <= 200; j++) {
            painter.drawPoint(i, j);
        }
    }
    */
}
