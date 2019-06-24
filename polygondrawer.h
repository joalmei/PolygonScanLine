#ifndef POLYGONDRAWER_H
#define POLYGONDRAWER_H

class CanvasOpenGL;
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include "drawer.h"
#include "qcolor.h"
#include "qpoint.h"
#include "qpainter.h"

#include "blocoet.h"
#include "lightsource.h"
#include "camera.h"

class PolygonDrawer : public Drawer
{
public:
    enum Shading {
        FLAT,
        GOURAUD,
        PHONG
    };

    std::vector<QPoint*> Vertices;

private:
    LightSource* light;
    Camera* camera;
    Shading shading;
    double extrusion = 50;

public:
    PolygonDrawer(CanvasOpenGL* canvas, LightSource* light, Camera* camera);
    virtual ~PolygonDrawer();
    void Draw(QColor pointsColor);

    void SetShading(Shading);

private:
    void oddEvenFillMethod(std::vector<QVector3D>& vertices, QColor& diffColor, std::vector<std::vector<int>>& zbuffer);

    // SCAN LINE HELPERS
    std::map<int, std::list<BlocoET>> prepareEt(std::vector<QVector3D>& vertices);
    void updateAET (int y, std::list<BlocoET>& aet, std::map<int, std::list<BlocoET>>& et);

    // Shading
    QColor shade(QVector3D& p, QColor& color);

    // Projection Helper
    std::vector<QVector3D> preparePoints();
};



#endif // POLYGONDRAWER_H
