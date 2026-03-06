#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLFunctions_1_0>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
    GLWidget(QWidget *parent = nullptr);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    QScopedPointer<QOpenGLShaderProgram> shaderProgram;
    QScopedPointer<QOpenGLShaderProgram> shaderProgram_border;
    QScopedPointer<QOpenGLTexture> planeTexture;
    QScopedPointer<QOpenGLTexture> cubeTexture;

    QOpenGLBuffer planeVBO;
    QOpenGLBuffer cubeVBO;

    QMatrix4x4 view;
    QMatrix4x4 model;
    QMatrix4x4 projection;

    QScopedPointer<QOpenGLFunctions_1_0> oldGL;
};

#endif // GLWIDGET_H
