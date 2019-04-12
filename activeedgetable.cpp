#include "activeedgetable.h"

ActiveEdgeTable::ActiveEdgeTable(vector<QPoint> Vertices) : ET(Vertices){

}

void ActiveEdgeTable::DrawAETMethod(QPainter& painter){
    size_t i = 0;

    while(((!AET.empty()) || (!ET.Tabela.empty())) && i < ALTURA){

        //Transfere o cesto i da ET na AET e ordena
        if(!ET.Tabela[i].empty()/*!ET.IsEmpty[i]*/){
            /*for(size_t j = 0; j < ET.Tabela[i].size(); j++){
                AET.push_back(ET.Tabela[i][j]);
            }*/
            for(int j = static_cast<int>(ET.Tabela[i].size()) - 1; j >= 0; j--){
                AET.push_back(ET.Tabela[i][static_cast<size_t>(j)]);
                ET.Tabela[i].pop_back();
            }
            sort(AET.begin(), AET.end());
        }

        //Retira os lados y = ymax
        for(size_t j = 0; j < AET.size(); j++){
            if(AET[j].get_ymax() == static_cast<int>(i)){
                if(AET.size() == 1){
                    AET.pop_back();
                }
                else{
                for(size_t k = j; k < AET.size() - 1; k++)
                    AET[k] = AET[k + 1];
                AET.pop_back();
                j--;
                }
            }
        }
        //Desenha os pixels na linha de varredura y usando pares de coordenadas x da AET
        if(AET.size() == 1){
            painter.drawPoint(FloatIntegerAdaptation(AET[0].get_x()), static_cast<int>(i));
        }
        else if(AET.size() > 1){
            for(size_t j = 0; j < AET.size() - 1; j++){
                for(int k = FloatIntegerAdaptation(AET[j].get_x()); k < FloatIntegerAdaptation(AET[j + 1].get_x()); k++){
                    painter.drawPoint(k, static_cast<int>(i));
                }
            }
        }
        //Incrementa y de 1 (no caso y = i)
        i++;
        //Para cada aresta nao vertical atualiza x = x + m
        for(size_t k = 0; k < AET.size(); k++){
            BlocoET b(AET[k].get_ymax(), AET[k].get_x() + AET[k].get_m(), AET[k].get_m());
            AET[k] = b;
        }
        //Reordena a AET
        sort(AET.begin(), AET.end());
    }
}

//Funcao para retornar x+1 caso seja float e x caso seja inteiro
int ActiveEdgeTable::FloatIntegerAdaptation(float x){
    int aux = static_cast<int>(10*x);
    if(aux%10 != 0)
        return static_cast<int>(x) + 1;
    else return static_cast<int>(x);
}
