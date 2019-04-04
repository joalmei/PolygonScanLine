#include "mousefollower.h"
#include <iostream>


MouseFollower::MouseFollower(QPoint* point, CanvasOpenGL* mouseCanvas) {
    mouseCanvas->OnMouseMoved.push_back([point](QMouseEvent* e) {
       point->setX(e->x());
       point->setY(e->y());
    });
}
