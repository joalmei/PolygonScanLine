#include "activeedgetable.h"

ActiveEdgeTable::ActiveEdgeTable(vector<QPoint> Vertices) : ET(Vertices){
    AET.resize(ALTURA);
}

void ActiveEdgeTable::DrawAETMethod(QPainter& painter){
    size_t i = 0;
    while(i < ALTURA){
        //Transfere o cesto i da ET na AET e ordena
        /*
        if(ET.NotEmpty[i]){
            for(size_t j = 0; j < ET.ET[i].size(); j++){
                AET[static_cast<size_t>(ET.NotEmpty[i])].push_back(ET.ET[i][j]);
                sort(AET[i].begin(), AET[i].end());
            }
        }/*
        //Retira os lados y = ymax
        for(size_t j = 0; j < AET[i].size(); j++){
            if(AET[i][j].get_ymax() == static_cast<int>(i)){
                for(size_t k = j; k < AET[i].size() - 1; k++)
                    AET[i][j] = AET[i][j + 1];
                AET[i].pop_back();
            }
        }
        //Desenha os pixels na linha de varredura y usando pares de coordenadas x da AET
        if(AET[i].size() == 1){
            painter.drawPoint(FloatIntegerAdaptation(AET[i][0].get_x()), static_cast<int>(i));
        }
        else if(AET[i].size() > 1){
            for(size_t j = 0; j < AET[i].size() - 1; j++){
                for(int k = FloatIntegerAdaptation(AET[i][j].get_x()); k < AET[i][j + 1].get_x(); k++){
                    painter.drawPoint(k, static_cast<int>(i));
                }
            }
        }
        //Incrementa y de 1 (no caso y = i)
        i++;
        //Para cada aresta nao vertical atualiza x = x + m
        for(size_t k = 0; k < AET[i].size(); k++){
            BlocoET b(AET[i][k].get_ymax(), AET[i][k].get_x() + AET[i][k].get_m(), AET[i][k].get_m());
            AET[i + 1].push_back(b);
        }
        //Reordena a AET
        sort(AET[i + 1].begin(), AET[i + 1].end());
*/i++;
    }
}

//Funcao para retornar x+1 caso seja float e x caso seja inteiro
int ActiveEdgeTable::FloatIntegerAdaptation(float x){
    int aux = static_cast<int>(10*x);
    if(aux%10 != 0)
        return static_cast<int>(x) + 1;
    else return static_cast<int>(x);
}
