#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    shaderProgram.reset(new QOpenGLShaderProgram);
    shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.glsl");
    shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment.glsl");
    shaderProgram->link();
    shaderProgram->bind();

    float vertices[]={
        0.3, 0.2,
        -0.3, 0.2,
        -0.3, -0.2,
        0.3, -0.2
    };

    VAO.reset(new QOpenGLVertexArrayObject);
    VAO->create();
    VAO->bind();

    vbo.reset(new QOpenGLBuffer);
    vbo->create();
    vbo->bind();
    vbo->allocate(vertices, sizeof(vertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);

    glEnable(GL_PROGRAM_POINT_SIZE);
}
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    VAO->bind();
    shaderProgram->bind();
    glDrawArrays(GL_QUADS, 0, 4);
}
