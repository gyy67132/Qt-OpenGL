#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLShaderProgram>
#include <QPointer>
#include <QtMath>
#include <QOpenGLBuffer>
#include <QWheelEvent>

#include "PointCloud.h"

class Camera
{
public:
    QVector3D position = {0, 0, 100};
    QVector3D front = {0, 0, -1};
    QVector3D up = {0, 1, 0};

    float yaw = 90.0f;
    float pitch = 0.0f;
    float distance = 2.0f;
    QVector3D target = QVector3D(0, 0, 0);

    QMatrix4x4 getViewMatrix()
    {
        //相机围绕target 0,0,0 转动， yaw=0时，相机在x轴正方向上，yaw=90，相机在z轴正方向上，pitch>0时，相机在y轴正方向上
        position.setX(target.x() + distance * qCos(pitch) * qCos(yaw));
        position.setY(target.y() + distance * qSin(pitch));
        position.setZ(target.z() + distance * qCos(pitch) * qSin(yaw));

        QMatrix4x4 view;
        view.lookAt(position, target, up);
        return view;
    }

    void rotate(float dx, float dy)
    {
        yaw+=dx;
        pitch+=dy;

        if(pitch >= 89.0) pitch = 89.0;
        else if(pitch <= -89.0) pitch = -89.0;
    }

    void zoom(float delta)
    {
        distance *= (1 - delta);
        if(distance < 0.1f) distance = 0.1f;
    }

    QMatrix4x4 getMVP(){
        //QMatrix4x4 view;
        //view.lookAt(position, position + front, up);


        QMatrix4x4 proj;
        proj.perspective(45.0f, 1.6f, 0.1f, 500.0f);

        return proj * getViewMatrix();
    }
};

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_2_Core
{
public:
    GLWidget(QWidget *parent = nullptr);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QPointer<QOpenGLShaderProgram> shaderProgram;
    std::unique_ptr<Octree> octree;
    std::unique_ptr<QOpenGLBuffer> VBO;

    Camera camera;
    PointClould pc;
};

#endif // GLWIDGET_H
