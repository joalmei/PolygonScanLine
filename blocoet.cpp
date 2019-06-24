#include "blocoet.h"

BlocoET::BlocoET(int ymin, int ymax, int xmin, int xmax, int zmin, int zmax) {
    this->ymax = ymax;

    this->x = static_cast<double>(xmin);
    this->z = static_cast<double>(zmin);

    this->mx = static_cast<double>(xmax - xmin) / static_cast<double>(ymax - ymin);
    this->mz = static_cast<double>(zmax - zmin) / static_cast<double>(ymax - ymin);
}

BlocoET::BlocoET(int ymax, double x, double mx, double z, double mz){
    this->ymax = ymax;

    this->x = x;
    this->z = z;

    this->mx = mx;
    this->mz = mz;
}

bool BlocoET::operator < (BlocoET obj){
    if(this->x < obj.x)
        return true;
    else {
        return false;
    }
}
