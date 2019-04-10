#ifndef ACTIVEEDGETABLE_H
#define ACTIVEEDGETABLE_H

#include "edgetable.h"
#include <qpainter.h>

class ActiveEdgeTable
{
public:
    ActiveEdgeTable(vector<QPoint> Vertices);
    void DrawAETMethod(QPainter& painter);
    int FloatIntegerAdaptation(float x);
private:
    EdgeTable ET;
    vector<vector<BlocoET>> AET;
};

#endif // ACTIVEEDGETABLE_H
