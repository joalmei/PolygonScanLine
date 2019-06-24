#ifndef BLOCOET_H
#define BLOCOET_H


class BlocoET
{
public:
    int ymax;
    double x, mx;
    double z, mz;
    double r, g, b, mr, mg, mb;

    BlocoET(int ymin, int ymax, int xmin, int xmax, int zmax, int zmin,
            double rmin = 0, double rmax = 0, double gmin = 0, double gmax = 0, double bmin = 0, double bmax = 0);

    bool operator < (BlocoET obj);
};

#endif // BLOCOET_H
