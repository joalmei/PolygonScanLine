#ifndef ACTIVEEDGETABLE_H
#define ACTIVEEDGETABLE_H

#include "edgetable.h"
#include <qpainter.h>
//#include "iostream"

class ActiveEdgeTable
{
public:
    ActiveEdgeTable(vector<QPoint> Vertices);
    void DrawAETMethod(QPainter& painter);
    int FloatIntegerAdaptation(float x);
//private:
    EdgeTable ET;
    vector<BlocoET> AET;
};

#endif // ACTIVEEDGETABLE_H
