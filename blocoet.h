#ifndef BLOCOET_H
#define BLOCOET_H


class BlocoET
{
public:
    int ymax;
    double x, m;

    BlocoET(int ymin, int ymax, int xmin, int xmax);
    BlocoET(int ymax, float x, float m);
    bool operator < (BlocoET obj);
};

#endif // BLOCOET_H
