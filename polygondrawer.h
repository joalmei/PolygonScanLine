#ifndef POLYGONDRAWER_H
#define POLYGONDRAWER_H

class CanvasOpenGL;
#include <vector>
#include <qcolor.h>
#include <qpoint.h>

class PolygonDrawer
{
public:
    PolygonDrawer();
    void Draw(CanvasOpenGL* canvas, std::vector<QPoint>& vertices, QColor pointsColor);
};

#endif // POLYGONDRAWER_H
