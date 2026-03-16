#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class GLWidget : public QOpenGLWidget , protected QOpenGLFunctions_4_2_Core
{
public:
    GLWidget(QWidget *parent);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    QScopedPointer<QOpenGLShaderProgram> shaderProgram;
    QScopedPointer<QOpenGLVertexArrayObject> VAO;
    QScopedPointer<QOpenGLBuffer> vbo;
};

#endif // GLWIDGET_H
