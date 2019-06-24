#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QVector3D>

class LightSource
{
public:
    enum Type {
        DIRECTIONAL,        // vector == direction
        POINT               // vector == position
    };

    LightSource(Type type, QVector3D* vector, double intensity = 1.0);

    double Diffuse(QVector3D& point, QVector3D& normal);
    std::pair<double, double> FullLighting(QVector3D& point, QVector3D& normal, QVector3D& view, double shininess);

private:
    Type type;
    QVector3D* vector;
    double intensity;
};

#endif // LIGHTSOURCE_H
