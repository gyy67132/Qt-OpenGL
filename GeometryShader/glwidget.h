#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class GLWidget : public QOpenGLWidget , protected QOpenGLFunctions_4_2_Core
{
public:
    GLWidget(QWidget *parent = nullptr);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
private:
    QScopedPointer<QOpenGLShaderProgram> shaderProgram;
    QScopedPointer<QOpenGLBuffer> vbo;
    QScopedPointer<QOpenGLVertexArrayObject> vao;
};

#endif // GLWIDGET_H
