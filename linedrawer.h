#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include "drawer.h"

class LineDrawer : public Drawer
{
public:
    std::pair<QPoint*, QPoint*> Points;

public:
    LineDrawer(CanvasOpenGL*);
    virtual ~LineDrawer();
    virtual void Draw(QColor pointsColor);
};

#endif // LINEDRAWER_H
