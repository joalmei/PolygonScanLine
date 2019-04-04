#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include "drawer.h"

class LineDrawer : public Drawer
{
public:
    std::pair<QPoint*, QPoint*> Points;

public:
    virtual ~LineDrawer();
    virtual void Draw(CanvasOpenGL* canvas, QColor pointsColor);
};

#endif // LINEDRAWER_H
