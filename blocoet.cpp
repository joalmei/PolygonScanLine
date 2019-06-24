#include "blocoet.h"

#include <iostream>

BlocoET::BlocoET(int ymin, int ymax, int xmin, int xmax, int zmin, int zmax, double lightmin, double lightmax) {
    this->ymax = ymax;

    this->x = static_cast<double>(xmin);
    this->z = static_cast<double>(zmin);
    this->light = static_cast<double>(lightmin);

    this->mx = static_cast<double>(xmax - xmin) / static_cast<double>(ymax - ymin);
    this->mz = static_cast<double>(zmax - zmin) / static_cast<double>(ymax - ymin);
    this->mlight = static_cast<double>(lightmax - lightmin) / static_cast<double>(ymax - ymin);
}

BlocoET::BlocoET(int ymax, double x, double mx, double z, double mz, double light, double mlight){
    this->ymax = ymax;

    this->x = x;
    this->z = z;
    this->light = light;

    this->mx = mx;
    this->mz = mz;
    this->mlight = mlight;
}

bool BlocoET::operator < (BlocoET obj){
    if(this->x < obj.x)
        return true;
    else {
        return false;
    }
}
