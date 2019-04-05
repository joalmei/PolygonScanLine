#include "vertexholderdrawer.h"
#include <vector>
#include <QPoint>
#include "linedrawer.h"

#define QUAD_EXTENT 5

VertexHolderDrawer::VertexHolderDrawer(CanvasOpenGL* canvas, QPoint* vertex) : Drawer(canvas){
    this->vertex = vertex;
}

VertexHolderDrawer::~VertexHolderDrawer() {
}

void VertexHolderDrawer::Draw(QColor color) {
    std::vector<QPoint> points = {
        QPoint(vertex->x() - QUAD_EXTENT, vertex->y()),
        QPoint(vertex->x(), vertex->y() + QUAD_EXTENT),
        QPoint(vertex->x() + QUAD_EXTENT, vertex->y()),
        QPoint(vertex->x(), vertex->y() - QUAD_EXTENT),
    };

    LineDrawer drawer(canvas);
    drawer.setWidth(isSelected ? 2 : 1);

    for (size_t i = 0; i < 4; i++) {
        drawer.Points = std::make_pair(&(points[i]), &(points[(i+1)%4]));
        drawer.Draw(color);
    }
}

QPoint* VertexHolderDrawer::Vertex() const {
    return vertex;
}

void VertexHolderDrawer::setIsSelected(const bool isSelected) {
    this->isSelected = isSelected;
}
