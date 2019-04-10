#ifndef BLOCOET_H
#define BLOCOET_H


class BlocoET
{
public:
    BlocoET(int ymin, int ymax, int xmin, int xmax);
    BlocoET(int ymax, float x, float m);
    bool operator < (BlocoET obj);
    int get_ymax();
    float get_x();
    float get_m();
    void set_x(float new_x);
private:
    int ymax;
    float x, m;
};

#endif // BLOCOET_H
