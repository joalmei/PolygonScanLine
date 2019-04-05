#ifndef VERTEXHOLDERDRAWER_H
#define VERTEXHOLDERDRAWER_H

#include "polygondrawer.h"

class VertexHolderDrawer : public Drawer
{
private:
    QPoint* vertex;
    bool isSelected = false;
public:
    VertexHolderDrawer(CanvasOpenGL*, QPoint*);
    virtual ~VertexHolderDrawer();
    virtual void Draw(QColor);

    QPoint* Vertex() const;

    void setIsSelected(const bool isSelected);
    bool IsSelected() const;
};

#endif // VERTEXHOLDERDRAWER_H
