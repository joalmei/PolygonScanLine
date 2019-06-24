#include "polygondrawer.h"
#include "canvasopengl.h"

#include "cgutils.h"

// ==================================================================================================
// PUBLIC MEMBERS
// ==================================================================================================
PolygonDrawer::PolygonDrawer(CanvasOpenGL* canvas, LightSource* light, Camera* camera) :
    Drawer(canvas), light(light), camera(camera), shading(Shading::FLAT) {}

// ==================================================================================================
PolygonDrawer::~PolygonDrawer() {}

// ==================================================================================================
void PolygonDrawer::Draw(QColor pointsColor) {
    // scan line algorithm

    std::vector<std::vector<int>> zbuffer(static_cast<size_t>(canvas->width()));
    for(size_t i = 0; i < zbuffer.size(); i++)
        zbuffer[i].resize(static_cast<size_t>(canvas->height()), 10000000);

    auto pts = preparePoints();
    oddEvenFillMethod(pts, pointsColor, zbuffer);
}

void PolygonDrawer::SetShading(PolygonDrawer::Shading shading) {
    this->shading = shading;
}

// ==================================================================================================
// PRIVATE MEMBERS
// ==================================================================================================
#include <iostream>

void PolygonDrawer::oddEvenFillMethod(std::vector<QVector3D>& vertices,
                                      QColor& diffColor,
                                      std::vector<std::vector<int>>& zbuffer) {
    //Aplica o ScanLine apenas para 2 ou mais pontos
    if (vertices.size() < 3) { return; }

    // Lighting
    QPainter painter(canvas);
    QPen myPen(diffColor);
    painter.setPen(myPen);

    // Inicializa a ET e a AET
    auto et = prepareEt(vertices);
    std::list<BlocoET> aet;

    int y = 0;
    while (!et.empty() || !aet.empty()) {
        updateAET(y, aet, et);

        //Desenha as linhas e incrementa os valores de x para a proxima iteracao
        auto it = aet.begin();
        while (it != aet.end()) {
            // 1st line
            auto x_beg = static_cast<int>(ceil(it->x));
            auto z_beg = static_cast<int>(ceil(it->z));
            it->x += it->mx;
            it->z += it->mz;
            it++;

            // 2nd line
            auto x_end = static_cast<int>(ceil(it->x));
            auto z_end = static_cast<int>(ceil(it->z));
            it->x += it->mx;
            it->z += it->mz;
            it++;

            // Z-BUFFER
            int x_init_z = -1;
            int x_end_z = -1;
            for (auto x = x_beg; x < x_end; x++) {
                auto z = static_cast<int>(z_beg + (z_end - z_beg)*(x - x_beg)/(x_end - x_beg));
                if (zbuffer[static_cast<size_t>(x)][static_cast<size_t>(y)] > z) {
                    if (x_init_z < 0) x_init_z = x;
                    x_end_z = x;
                    zbuffer[static_cast<size_t>(x)][static_cast<size_t>(y)] = z;
                }
            }

            painter.drawLine(x_init_z, y, x_end_z, y);
        }

        y++;
    }
}


std::map<int, std::list<BlocoET>> PolygonDrawer::prepareEt(std::vector<QVector3D>& vertices) {
    std::map<int, std::list<BlocoET>> et;
    for (size_t i = 0; i < vertices.size(); i++) {
        // a -> b
        QVector3D a = vertices[i];
        QVector3D b = vertices[(i+1) % vertices.size()];

        if (static_cast<int>(a.y()) == static_cast<int>(b.y())) { continue; }
        if (a.y() > b.y()) {
            auto swap = a;
            a = b;
            b = swap;
        }

        BlocoET aux(static_cast<int>(a.y()), static_cast<int>(b.y()), static_cast<int>(a.x()), static_cast<int>(b.x()), static_cast<int>(a.z()), static_cast<int>(b.z()));
        et[static_cast<int>(a.y())].push_back(aux);
    }
    return et;
}

void PolygonDrawer::updateAET (int y, std::list<BlocoET>& aet, std::map<int, std::list<BlocoET>>& et) {
    //Remove todos os pontos cujo y = ymax
    aet.remove_if([y](const BlocoET val) { return val.ymax == y; });

    //Transfere os valores da ET na posicao y para a AET
    auto etvals = et[y];
    aet.insert(aet.end(), etvals.begin(), etvals.end());
    et.erase(y);

    //Ordena se necessário
    aet.sort([](const BlocoET &b1, const BlocoET &b2) { return (b1.x < b2.x); });
}

QColor PolygonDrawer::shade(QVector3D& point, QColor& color) {
    // Lighting
    auto normal = QVector3D(0, 0, -1);

    auto diff = light->Diffuse(point, normal);
    return QColor(static_cast<int>(color.red() * diff),
                  static_cast<int>(color.green() * diff),
                  static_cast<int>(color.blue() * diff));
}

std::vector<QVector3D> PolygonDrawer::preparePoints() {
    std::vector<QVector3D> points;
    for (auto v : Vertices) {
        points.push_back(QVector3D(v->x(), v->y(), 0));
    }

    QMatrix4x4 t1;
    t1.translate(-canvas->width()/2, -canvas->height()/2, 0);
    QMatrix4x4 t2;
    t2.translate(canvas->width()/2, canvas->height()/2, 0);
    QMatrix4x4 transform;
    auto rotation = camera->GetRotation();
    transform.rotate(rotation.x(), 1, 0, 0);
    transform.rotate(rotation.y(), 0, 1, 0);
    transform.rotate(rotation.z(), 0, 0, 1);

    for (size_t i = 0; i < points.size(); i++) {
        //std::cout << "before : " << points[i].x() << " " << points[i].y() << " " << points[i].z() << std::endl;
        points[i] = t1 * points[i];
        points[i] = transform * points[i];
        points[i] = t2 * points[i];
        //std::cout << "after : " << points[i].x() << " " << points[i].y() << " " << points[i].z() << std::endl;
    }

    return points;
}




//            QLinearGradient linearGrad(x_beg, y, x_end, y);
//            QVector3D start (x_beg, y, 0);
//            QVector3D end (x_end, y, 0);
//            auto startColor = shade(start, diffColor);
//            auto endColor = shade(end, diffColor);
//            linearGrad.setColorAt(0, startColor);
//            linearGrad.setColorAt(1, endColor);
//            QPen myPen(diffColor);
//            QBrush brush(linearGrad);
//            myPen.setBrush(brush);
//            painter.setPen(myPen);

//auto normal = QVector3D::normal(QVector3D(vertices[0]->x() - vertices[1]->x(),vertices[0]->y() - vertices[1]->y(), vertices[0]->y() - vertices[1]->y()),
//                                QVector3D(vertices[2]->x() - vertices[1]->x(),vertices[2]->y() - vertices[1]->y(), vertices[2]->y() - vertices[1]->y()));
//if (shading == Shading::FLAT) {
//    auto intensity = clamp01(static_cast<double>(QVector3D::dotProduct(camera->GetRotation(), (-1)*normal)));

//    diffColor.setRgbF(diffColor.redF() * intensity,
//                      diffColor.greenF() * intensity,
//                      diffColor.blueF() * intensity);

//    QPen myPen(diffColor);
//    painter.setPen(myPen);
//}
//transform.rotate(static_cast<float>(45), 1, 0, 0);
//transform.frustum(1, 0, 1, 0, 10, 40);
//transform.lookAt(QVector3D(0, 0, 10), QVector3D(0, 10, 0), QVector3D(0, 1, 0));
