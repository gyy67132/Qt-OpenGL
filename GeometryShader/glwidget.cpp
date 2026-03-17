#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    // QSurfaceFormat format;
    // format.setVersion(4, 2);
    // format.setProfile(QSurfaceFormat::CoreProfile);
    // setFormat(format);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    qDebug() << (const char*)glGetString(GL_VERSION);
    qDebug() << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

    shaderProgram.reset(new QOpenGLShaderProgram);
    shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.glsl");
    shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Geometry, ":/geometry.glsl");
    shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":/fragment.glsl");
    shaderProgram->link();

    vao.reset(new QOpenGLVertexArrayObject);
    vao->bind();

    float points[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 左上
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f,// 右上
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f,// 右下
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f // 左下
    };

    vbo.reset(new QOpenGLBuffer);
    vbo->create();
    vbo->bind();
    vbo->allocate(points, sizeof(points));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)(2*sizeof(GL_FLOAT)));
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    vao->bind();
    shaderProgram->bind();
    glDrawArrays(GL_POINTS, 0 ,4);
}
