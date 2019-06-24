#include "lightsource.h"
#include <utility>
#include <QtMath>
#include <iostream>
#include "cgutils.h"

LightSource::LightSource(LightSource::Type type, QVector3D *vector, double intensity) :
    type(type), vector(vector), intensity(intensity) {
}

double LightSource::Diffuse(QVector3D &point, QVector3D &normal) {
    auto l = type == Type::POINT ? (*vector - point).normalized() : -1.0 * vector->normalized();
    auto n = normal.normalized();

//    std::cout << intensity * static_cast<double>(QVector3D::dotProduct(l, n)) << std::endl;


    return clamp01(intensity * static_cast<double>(QVector3D::dotProduct(l, n)));
}

std::pair<double, double> LightSource::FullLighting(QVector3D& point, QVector3D &normal,
                                                    QVector3D& view, double shininess) {
    auto l = type == Type::POINT ? (*vector - point).normalized() : -1.0 * vector->normalized();
    auto n = normal.normalized();

    auto cosTheta = clamp01(QVector3D::dotProduct(l, n));

    auto s = (view - point).normalized();
    auto r = 2 * cosTheta * n - l;

    auto cosAlpha = clamp01(QVector3D::dotProduct(s, r));

    return std::make_pair(intensity * static_cast<double>(cosTheta),
                          intensity * pow(static_cast<double>(cosAlpha), shininess));
}


