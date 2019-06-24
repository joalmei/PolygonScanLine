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

#include <map>
#include <vector>

using namespace std;

class PolygonDrawer : public Drawer
{
public:
    enum Shading {
        FLAT,
        GOURAUD,
        PHONG
    };

    vector<QPoint*> Vertices;

private:
    LightSource* light;
    Camera* camera;
    Shading shading;
    float extrusion = 50;

public:
    PolygonDrawer(CanvasOpenGL* canvas, LightSource* light, Camera* camera);
    virtual ~PolygonDrawer();
    void Draw(QColor pointsColor);

    void SetShading(Shading);

private:
    void oddEvenFillMethod(vector<QVector3D>& vertices, QColor& diffColor, vector<vector<int>>& zbuffer);

    // SCAN LINE HELPERS
    map<int, list<BlocoET>> prepareEt(vector<QVector3D>& vertices);
    void updateAET (int y, list<BlocoET>& aet, map<int, list<BlocoET>>& et);

    // Shading
    QColor shade(QVector3D& p, QColor& color);

    // Projection Helper
    vector<vector<QVector3D>> preparePoints();
};



#endif // POLYGONDRAWER_H
