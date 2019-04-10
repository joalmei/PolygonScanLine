#include "blocoet.h"

BlocoET::BlocoET(int ymin, int ymax, int xmin, int xmax)
{
    this->ymax = ymax;
    this->x = static_cast<float>(xmin);
    this->m = (static_cast<float>(xmax - xmin) / (ymax - ymin));
}

BlocoET::BlocoET(int ymax, float x, float m){
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

int BlocoET::get_ymax(){
    return ymax;
}

float BlocoET::get_x(){
    return x;
}
float BlocoET::get_m(){
    return m;
}

void BlocoET::set_x(float new_x){
    x = new_x;
}
