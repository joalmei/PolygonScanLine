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
    float extrusion = 100;
    double cteAmb = 0.2;
    double cteDiff = 3.9;
    double cteSpec = 0.8;
    double shininess = 3;

public:
    PolygonDrawer(CanvasOpenGL* canvas, LightSource* light, Camera* camera);
    virtual ~PolygonDrawer();
    void Draw(QColor pointsColor);

    void SetShading(Shading);

private:
    void oddEvenFillMethodFLAT(vector<QVector3D*>& vertices,
                           QColor& diffColor,
                           vector<vector<int>>& zbuffer);

    void oddEvenFillMethodGOURAULD(vector<QVector3D*>& vertices,
                           map<QVector3D*, QVector3D>& normals,
                           QColor& diffColor,
                           vector<vector<int>>& zbuffer);

    // SCAN LINE HELPERS
    map<int, list<BlocoET>> prepareEt(vector<QVector3D*>& vertices);
    map<int, list<BlocoET>> prepareEt(vector<QVector3D*>& vertices, map<QVector3D*, QVector3D>& normals, QColor& paintColor);
    void updateAET (int y, list<BlocoET>& aet, map<int, list<BlocoET>>& et);

    // Shading
    QColor shade(QVector3D& p, QVector3D& normal, QColor& paintColor);
    QColor flatColor(QVector3D& n, QColor& c);

    // Projection Helper
    // returns all faces and all normals to all vetices
    pair<vector<vector<QVector3D*>>, map<QVector3D*, QVector3D>> preparePoints();

    void printScanLine(int xbeg, int xend, QColor& cbeg, QColor& cend, QPainter& painter);
};



#endif // POLYGONDRAWER_H
