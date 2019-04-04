#include "mousefollower.h"
#include <iostream>


MouseFollower::MouseFollower(CanvasOpenGL* mouseCanvas) {
    mouseCanvas->OnMouseMoved.push_back([this](QMouseEvent* e) {
       for(auto point : this->following) {
           point->setX(e->x());
           point->setY(e->y());
       }
    });
}

void MouseFollower::AddPoint(QPoint* point) {
    following.insert(point);
}
void MouseFollower::RemovePoint(QPoint* point) {
    following.erase(point);
}
