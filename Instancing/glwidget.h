#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_2_Core>
#include <QPointer>
#include <QOpenGLShaderProgram>
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
    QPointer<QOpenGLShaderProgram> shaderProgram;
    QSharedPointer<QOpenGLBuffer> VBO;
    QSharedPointer<QOpenGLBuffer> instanceVBO;
    QPointer<QOpenGLVertexArrayObject> VAO;
    QVector2D offsets[100];
};

#endif // GLWIDGET_H
