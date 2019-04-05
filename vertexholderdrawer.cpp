#include "vertexholderdrawer.h"
#include <vector>
#include <QPoint>

#define QUAD_EXTENT 2

VertexHolderDrawer::VertexHolderDrawer(CanvasOpenGL* canvas, QPoint* vertex) : Drawer(canvas){
    this->vertex = vertex;
    polygonDrawer = new PolygonDrawer(canvas);
    polygonDrawer->Vertices = {
        new QPoint(vertex->x() - QUAD_EXTENT, vertex->y()),
        new QPoint(vertex->x() + QUAD_EXTENT, vertex->y()),
        new QPoint(vertex->x(), vertex->y() - QUAD_EXTENT),
        new QPoint(vertex->x(), vertex->y() + QUAD_EXTENT),
    };
}

VertexHolderDrawer::~VertexHolderDrawer() {
    delete polygonDrawer;
}

void VertexHolderDrawer::Draw(QColor color) {
    polygonDrawer->Vertices[0]->setX(vertex->x() - QUAD_EXTENT);
    polygonDrawer->Vertices[0]->setY(vertex->y());

    polygonDrawer->Vertices[1]->setX(vertex->x() + QUAD_EXTENT);
    polygonDrawer->Vertices[1]->setY(vertex->y());

    polygonDrawer->Vertices[2]->setX(vertex->x());
    polygonDrawer->Vertices[2]->setY(vertex->y() - QUAD_EXTENT);

    polygonDrawer->Vertices[3]->setX(vertex->x());
    polygonDrawer->Vertices[3]->setY(vertex->y() + QUAD_EXTENT);

    return polygonDrawer->Draw(color);
}

QPoint* VertexHolderDrawer::Vertex() const {
    return vertex;
}
