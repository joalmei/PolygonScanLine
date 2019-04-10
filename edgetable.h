#ifndef EGDETABLE_H
#define EGDETABLE_H

#include "blocoet.h"

#include <qpoint.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>

#define COMPRIMENTO 600
#define ALTURA 460

using namespace std;

class EdgeTable
{
public:
    EdgeTable(vector<QPoint> Pontos);

    vector<bool> IsEmpty;
    vector<vector<BlocoET>> ET;

    void DrawAETMethod();
};

#endif // EGDETABLE_H
