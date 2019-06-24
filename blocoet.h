#ifndef BLOCOET_H
#define BLOCOET_H


class BlocoET
{
public:
    int ymax;
    double x, mx;
    double z, mz;
    double light, mlight;

    BlocoET(int ymin, int ymax, int xmin, int xmax, int zmax, int zmin, double lightmin = 0, double lightmax = 0);
    BlocoET(int ymax, double x, double mx, double z, double mz, double light = 0, double mlight = 0);
    bool operator < (BlocoET obj);
};

#endif // BLOCOET_H
