#include "camera.h"
#include <QMatrix4x4>

Camera::Camera(QVector3D pos, QVector3D rot) :pos(pos), rot(rot) { }

QVector3D Camera::GetPosition() const {
    return this->pos;
}

QVector3D Camera::GetRotation() const {
    return this->rot;
}

void Camera::SetRotation(QVector3D& euler) {
    this->rot = euler;
}

void Camera::Translate(QVector3D &dt) {
    pos += dt;
}

void Camera::Rotate(QVector3D &dr) {
    rot += dr;
}
