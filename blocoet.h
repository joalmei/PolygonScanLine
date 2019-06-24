#ifndef BLOCOET_H
#define BLOCOET_H


class BlocoET
{
public:
    int ymax;
    double x, mx;
    double z, mz;

    BlocoET(int ymin, int ymax, int xmin, int xmax, int zmax, int zmin);
    BlocoET(int ymax, double x, double mx, double z, double mz);
    bool operator < (BlocoET obj);
};

#endif // BLOCOET_H
