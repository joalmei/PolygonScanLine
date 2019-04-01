#ifndef POLYGONDRAWER_H
#define POLYGONDRAWER_H

class CanvasOpenGL;
#include <vector>
#include "qcolor.h"
#include "qpoint.h"
#include "qpainter.h"

class PolygonDrawer
{
public:
    PolygonDrawer();
    void Draw(CanvasOpenGL* canvas, std::vector<QPoint>& vertices, QColor pointsColor);

private:
    void MidPointMethod(std::vector<QPoint>& vertices, QPainter& painter);
};

#endif // POLYGONDRAWER_H
