#ifndef VERTEXHOLDERDRAWER_H
#define VERTEXHOLDERDRAWER_H

#include "polygondrawer.h"

class VertexHolderDrawer : public Drawer
{
private:
    PolygonDrawer* polygonDrawer;
    QPoint* vertex;
public:
    VertexHolderDrawer(CanvasOpenGL*, QPoint*);
    virtual ~VertexHolderDrawer();
    virtual void Draw(QColor);
    QPoint* Vertex() const;
};

#endif // VERTEXHOLDERDRAWER_H
