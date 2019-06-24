#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>

class Camera
{
private:
    QVector3D pos;
    QVector3D rot;

public:
    Camera(QVector3D pos, QVector3D rot);

    QVector3D GetPosition() const;
    QVector3D GetRotation() const;
    void SetRotation(QVector3D& );

    void Translate(QVector3D&);
    void Rotate(QVector3D&);
};

#endif // CAMERA_H
