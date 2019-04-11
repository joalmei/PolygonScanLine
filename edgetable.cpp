#include "edgetable.h"

EdgeTable::EdgeTable(vector<QPoint> Pontos){//Funcao que preenche a EdgeTable

    if(Pontos.size() <= 1)
        return;

    Tabela.resize(ALTURA);
    IsEmpty.resize(ALTURA, true);

    for(size_t i = 0; i < (Pontos.size()) - 1; i++){//Percorre todos os pontos menos o ultimo
        if(Pontos[i].y() < Pontos[i + 1].y()){//Quando i eh o ponto minimo

            //Cria um bloco (uma reta) com i como ponto minimo e i+1 como ponto maximo
            BlocoET b(Pontos[i].y(), Pontos[i + 1].y(), Pontos[i].x(), Pontos[i + 1].x());

            //Aloca o bloco na posicao ymin da EdgeTable e ordena os blocos existentes na posicao ymin em ordem crescente de x
            Tabela[static_cast<size_t>(Pontos[i].y())].push_back(b);
            sort(Tabela[static_cast<size_t>(Pontos[i].y())].begin(), Tabela[static_cast<size_t>(Pontos[i].y())].end());

            //Adiciona ao vetor IsEmpty na posicao i o valor false
            IsEmpty[static_cast<size_t>(Pontos[i].y())] = false;
        }
        else if(Pontos[i].y() > Pontos[i + 1].y()){//Quando i+1 eh o ponto minimo

            //Cria um bloco (uma reta) com i como ponto minimo e i+1 como ponto maximo
            BlocoET b(Pontos[i + 1].y(), Pontos[i].y(), Pontos[i + 1].x(), Pontos[i].x());

            //Aloca o bloco na posicao ymin da EdgeTable e ordena os blocos existentes na posicao ymin em ordem crescente de x
            Tabela[static_cast<size_t>(Pontos[i + 1].y())].push_back(b);
            sort(Tabela[static_cast<size_t>(Pontos[i + 1].y())].begin(), Tabela[static_cast<size_t>(Pontos[i + 1].y())].end());

            //Adiciona ao vetor NotEmpty na posicao i+1 o valor false
            IsEmpty[static_cast<size_t>(Pontos[i + 1].y())] = false;
        }
        //Quando os y dos pontos são iguais eles formam uma aresta horizontal, portanto se ignora
    }

    size_t N = Pontos.size() - 1;

    //Coloca o ultimo bloco (ultima reta), que depende do ultimo ponto e o primeiro
    if(Pontos[N].y() < Pontos[0].y()){
        BlocoET b(Pontos[N].y(), Pontos[0].y(), Pontos[N].x(), Pontos[0].x());
        Tabela[static_cast<size_t>(Pontos[N].y())].push_back(b);
        sort(Tabela[static_cast<size_t>(Pontos[N].y())].begin(), Tabela[static_cast<size_t>(Pontos[N].y())].end());
        IsEmpty[static_cast<size_t>(Pontos[N].y())] = false;
    }
    else if(Pontos[N].y() > Pontos[0].y()) {
        BlocoET b(Pontos[0].y(), Pontos[N].y(), Pontos[0].x(), Pontos[N].x());
        Tabela[static_cast<size_t>(Pontos[0].y())].push_back(b);
        sort(Tabela[static_cast<size_t>(Pontos[0].y())].begin(), Tabela[static_cast<size_t>(Pontos[0].y())].end());
        IsEmpty[static_cast<size_t>(Pontos[0].y())] = false;
    }
}

