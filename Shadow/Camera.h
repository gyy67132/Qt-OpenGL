#ifndef CAMERA_H
#define CAMERA_H

#include <QtMath>
#include <QVector3D>
#include <QMatrix4x4>

class Camera{
public:
    Camera(QVector3D eyeValue = QVector3D(0, 1, 6), QVector3D centerValue = QVector3D(0,1,0), QVector3D worldUpValue = QVector3D(0, 1, 0))
    {
        eye = eyeValue;
        center = centerValue;
        worldUp = worldUpValue;

        front = center - eye;
        right = QVector3D::crossProduct(front, worldUp);
        up = QVector3D::crossProduct(right, front);
    }

    QMatrix4x4 viewMartix()
    {
        QMatrix4x4 m;
        m.lookAt(eye, center, up);
        return m;
    }

    void back()
    {
        eye -= front * velocity;
    }
    void forward()
    {
        eye += front * velocity;
    }
    void left()
    {
        eye -= right * velocity;
    }
    void towardsTheRight()
    {
        eye += right * velocity;
    }
    void upward()
    {
        eye += up * velocity * 0.1;
        center = eye + front;
    }
    void down()
    {
        eye -= up * velocity * 0.1;;
        center = eye + front;
    }
    void rotate(int xChange, int yChange)
    {
        float adjust = 0.2;
        pitch += adjust *yChange;
        yaw += adjust * xChange;
        updateVectors();
    }
    void updateVectors()
    {
        front.setX(qCos(qDegreesToRadians(pitch)) * qCos(qDegreesToRadians(yaw)));
        front.setY(qSin(qDegreesToRadians(pitch)));
        front.setZ(qCos(qDegreesToRadians(pitch)) * qSin(qDegreesToRadians(yaw)));

        center = eye + front;
    }
    void restore()
    {
        yaw = -90;
        pitch = 0;
        eye = QVector3D(0, 0, 6);
        center = QVector3D(0,0,0);
        worldUp = QVector3D(0, 1, 0);
        front = center - eye;
        right = QVector3D::crossProduct(front, worldUp);
        up = QVector3D::crossProduct(right, front);
    }
    QVector3D cameraPos()
    {
        return eye;
    }
private:
    QVector3D eye;
    QVector3D center;
    QVector3D worldUp;
    QVector3D up;
    QVector3D front;
    QVector3D right;
    float velocity = 0.05;
    float yaw = -90;
    float pitch = 0;
};


#endif // CAMERA_H
