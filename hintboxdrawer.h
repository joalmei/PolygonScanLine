#ifndef HINTBOXDRAWER_H
#define HINTBOXDRAWER_H

#include "drawer.h"

class HintBoxDrawer: public Drawer
{
public:
    QString Text;

public:
    virtual ~HintBoxDrawer();
    virtual void Draw(CanvasOpenGL* canvas, QColor pointsColor);
};

#endif // HINTBOXDRAWER_H
