#ifndef BLOCOET_H
#define BLOCOET_H

#include <QVector3D>

class BlocoET
{
public:
    int ymax;
    double x, mx;
    double z, mz;
    double r, g, b, mr, mg, mb;
    QVector3D n, mn;

    BlocoET(int ymin, int ymax, int xmin, int xmax, int zmin, int zmax);

    // GOURAUD
    BlocoET(int ymin, int ymax, int xmin, int xmax, int zmin, int zmax,
            double rmin, double rmax, double gmin, double gmax, double bmin, double bmax);

    // PHONG
    BlocoET(int ymin, int ymax, int xmin, int xmax, int zmin, int zmax,
            QVector3D& nmin, QVector3D& nmax);

    bool operator < (BlocoET obj);
};

#endif // BLOCOET_H
