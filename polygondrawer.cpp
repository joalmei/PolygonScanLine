#include "polygondrawer.h"
#include "canvasopengl.h"

// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
PolygonDrawer::PolygonDrawer(CanvasOpenGL* canvas) : Drawer(canvas) { }

// ==================================================================================================
PolygonDrawer::~PolygonDrawer() {}

// ==================================================================================================
void PolygonDrawer::Draw(QColor pointsColor) {
    //create a QPainter and pass a pointer to the device.
    //A paint device can be a QWidget, a QPixmap or a QImage
    QPainter painter(canvas);

    QPen myPen(pointsColor);
    painter.setPen(myPen);

    // scan line algorithm
    oddEvenFillMethod(Vertices, painter);
}

// ==================================================================================================
// PRIVATE MEMBERS
// ==================================================================================================


void PolygonDrawer::oddEvenFillMethod(std::vector<QPoint*>& vertices, QPainter& painter) {
    //Aplica o AET apenas para 2 ou mais pontos
    if (vertices.size() < 2) { return; }

    //Rotina para preencher a EdgeTable
    std::map<int, std::list<BlocoET>> et;
    for (size_t i = 0; i < vertices.size(); i++) {
        // a -> b
        QPoint* a = vertices[i];
        QPoint* b = vertices[(i+1) % vertices.size()];

        if (a->y() == b->y()) { continue; }
        if (a->y() > b->y()) {
            auto swap = a;
            a = b;
            b = swap;
        }

        BlocoET aux(a->y(), b->y(), a->x(), b->x());
        et[a->y()].push_back(aux);
    }

    //Cria a AET vazia
    std::list<BlocoET> aet;

    int y = 0;
    while (!et.empty() || !aet.empty()) {
        //Remove todos os pontos cujo y = ymax
        aet.remove_if([y](const BlocoET val) { return val.ymax == y; });

        //Transfere os valores da ET na posicao y para a AET
        auto etvals = et[y];
        aet.insert(aet.end(), etvals.begin(), etvals.end());
        et.erase(y);

        //Ordena se necessário
        aet.sort([](const BlocoET &b1, const BlocoET &b2) { return (b1.x < b2.x); });

        //Desenha as linhas e incrementa os valores de x para a proxima iteracao
        auto it = aet.begin();
        while (it != aet.end()) {
            // get x for print
            auto x_beg = (ceil(it->x));

            // update point
            it->x += it->m;
            it++;

            auto x_end = (ceil(it->x));

            // update point
            it->x += it->m;
            it++;

            painter.drawLine(static_cast<int>(x_beg), y, static_cast<int>(x_end) - 1, y);
        }

        y++;
    }
}
