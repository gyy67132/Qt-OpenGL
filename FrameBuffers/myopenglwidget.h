#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>

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
    QOpenGLVertexArrayObject vaoCube;
    QOpenGLVertexArrayObject vaoQuad;
    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer vertexBufferCube;
    QOpenGLBuffer vertexBufferQuad;
    QScopedPointer<QOpenGLShaderProgram> shaderProgram;
    QScopedPointer<QOpenGLShaderProgram> shaderProgramQuad;

    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;

    QScopedPointer<QOpenGLTexture> texture;
    QScopedPointer<QOpenGLTexture> textureCube;
    QScopedPointer<QOpenGLFramebufferObject> fbo;
    QScopedPointer<QOpenGLTexture> fboTexture;
};

#endif // MYOPENGLWIDGET_H
