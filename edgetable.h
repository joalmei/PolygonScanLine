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

    vector<vector<BlocoET>> Tabela;
    vector<bool> VariavelQueNaoFazNadaMasSeTirarCrasha;

    //int LastElement;

    void DrawAETMethod();
};

#endif // EGDETABLE_H
