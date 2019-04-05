#ifndef DRAWER_H
#define DRAWER_H

#include "qcolor.h"
#include "qpoint.h"
#include <QObject>

class CanvasOpenGL;

class Drawer : public QObject {
protected:
    CanvasOpenGL* canvas;
public:
    Drawer(CanvasOpenGL* canvas);
    virtual ~Drawer();
    virtual void Draw(QColor pointsColor) = 0;
};

#endif // DRAWER_H
