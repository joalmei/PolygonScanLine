#ifndef POLYGONDRAWER_H
#define POLYGONDRAWER_H

class CanvasOpenGL;
#include <vector>
#include "drawer.h"
#include "qcolor.h"
#include "qpoint.h"
//#include "qpainter.h" incluso no activeedgetable.h
#include "activeedgetable.h"

class PolygonDrawer : public Drawer
{
public:
    std::vector<QPoint*> Vertices;

public:
    PolygonDrawer(CanvasOpenGL* canvas);
    virtual ~PolygonDrawer();
    void Draw(QColor pointsColor);
    void AETMethod(vector<QPoint> points, QPainter& painter);

private:
    void oddEvenFillMethod(std::vector<QPoint*>& vertices, QPainter& painter);
};



#endif // POLYGONDRAWER_H
