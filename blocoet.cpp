#include "blocoet.h"

BlocoET::BlocoET(int ymin, int ymax, int xmin, int xmax)
{
    this->ymax = ymax;
    this->x = static_cast<double>(xmin);
    this->m = (static_cast<double>(xmax - xmin) / (ymax - ymin));
}

BlocoET::BlocoET(int ymax, double x, double m){
    this->ymax = ymax;
    this->x = x;
    this->m = m;
}

bool BlocoET::operator < (BlocoET obj){
    if(this->x < obj.x)
        return true;
    else {
        return false;
    }
}
