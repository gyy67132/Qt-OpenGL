#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
    MyOpenGLWidget(QWidget *parent);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:

    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vertexBuffer;
    QScopedPointer<QOpenGLShaderProgram> shaderProgram;

    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;
};

#endif // MYOPENGLWIDGET_H
