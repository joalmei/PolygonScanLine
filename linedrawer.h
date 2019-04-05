#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include "drawer.h"

class LineDrawer : public Drawer
{
public:
    std::pair<QPoint*, QPoint*> Points;
    qreal width = 1;

public:
    LineDrawer(CanvasOpenGL*);
    virtual ~LineDrawer();
    virtual void Draw(QColor pointsColor);
    void setWidth(const qreal);
};

#endif // LINEDRAWER_H
