#ifndef MOUSEFOLLOWER_H
#define MOUSEFOLLOWER_H

#include <qpoint.h>
#include "canvasopengl.h"
#include <unordered_set>

class MouseFollower
{
private:
    std::unordered_set<QPoint*> following;

public:
    MouseFollower(CanvasOpenGL*);
    void AddPoint(QPoint*);
    void RemovePoint(QPoint*);
};

#endif // MOUSEFOLLOWER_H
