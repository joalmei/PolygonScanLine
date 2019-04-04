#ifndef DRAWER_H
#define DRAWER_H

#include <vector>
#include "qcolor.h"
#include "qpoint.h"

class CanvasOpenGL;

class Drawer
{
public:
    virtual ~Drawer();
    virtual void Draw(CanvasOpenGL* canvas, std::vector<QPoint>& vertices, QColor pointsColor) = 0;
};

#endif // DRAWER_H
