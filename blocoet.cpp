#include "blocoet.h"

#include <iostream>

BlocoET::BlocoET(int ymin, int ymax, int xmin, int xmax, int zmin, int zmax) {
    this->ymax = ymax;

    this->x = static_cast<double>(xmin);
    this->z = static_cast<double>(zmin);

    this->mx = static_cast<double>(xmax - xmin) / static_cast<double>(ymax - ymin);
    this->mz = static_cast<double>(zmax - zmin) / static_cast<double>(ymax - ymin);
}

BlocoET::BlocoET(int ymin, int ymax, int xmin, int xmax, int zmin, int zmax,
                 double rmin, double rmax, double gmin, double gmax, double bmin, double bmax)
    : BlocoET(ymin, ymax, xmin, xmax, zmin, zmax) {

    this->r = static_cast<double>(rmin);
    this->g = static_cast<double>(gmin);
    this->b = static_cast<double>(bmin);

    this->mr = static_cast<double>(rmax - rmin) / static_cast<double>(ymax - ymin);
    this->mg = static_cast<double>(gmax - gmin) / static_cast<double>(ymax - ymin);
    this->mb = static_cast<double>(bmax - bmin) / static_cast<double>(ymax - ymin);
}

BlocoET::BlocoET(int ymin, int ymax, int xmin, int xmax, int zmin, int zmax,
                 QVector3D &nmin, QVector3D &nmax)
    : BlocoET(ymin, ymax, xmin, xmax, zmin, zmax) {
    this->n = nmin;
    this->mn = (nmax - nmin) / static_cast<float>(ymax - ymin);
}

bool BlocoET::operator < (BlocoET obj){
    if(this->x < obj.x)
        return true;
    else {
        return false;
    }
}
