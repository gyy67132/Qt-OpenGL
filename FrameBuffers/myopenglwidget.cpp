#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent):QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    vao.create();
    vao.bind();

    // float planeVertices[] = {
    //     // positions          // texture Coords
    //     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    //     -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    //     -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

    //     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    //     -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    //     5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    // };

    float planeVertices[] = {
        // 位置              // 纹理坐标
        1.0f,  1.0f, 0.0f,  1.0f, 1.0f, // 右上
        1.0f, -1.0f, 0.0f,  1.0f, 0.0f, // 右下
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, // 左下
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f  // 左上
    };

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.allocate(planeVertices, sizeof(planeVertices));

    shaderProgram.reset(new QOpenGLShaderProgram);
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":vertex.glsl");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":fragment.glsl");
    shaderProgram->link();

    shaderProgram->bind();
    vertexBuffer.bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MyOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.3, 0.3, 1.0);

    shaderProgram->bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

}
