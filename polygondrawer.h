#ifndef POLYGONDRAWER_H
#define POLYGONDRAWER_H

class CanvasOpenGL;
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include "drawer.h"
#include "qcolor.h"
#include "qpoint.h"
#include "qpainter.h"

#include "blocoet.h"

class PolygonDrawer : public Drawer
{
public:
    std::vector<QPoint*> Vertices;

public:
    PolygonDrawer(CanvasOpenGL* canvas);
    virtual ~PolygonDrawer();
    void Draw(QColor pointsColor);

private:
    void oddEvenFillMethod(std::vector<QPoint*>& vertices, QPainter& painter);
};



#endif // POLYGONDRAWER_H
