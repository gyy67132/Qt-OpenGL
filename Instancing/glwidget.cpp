#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    float quadVertices[] = {
        // 位置          // 颜色
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };

    shaderProgram = new QOpenGLShaderProgram;
    shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.glsl");
    shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment.glsl");
    if(!shaderProgram->link()){
        qDebug()<<"Shader link error "<< shaderProgram->log();
    }

    VAO = new QOpenGLVertexArrayObject;
    VAO->create();
    VAO->bind();

    VBO.reset(new QOpenGLBuffer);
    VBO->create();
    VBO->bind();
    VBO->allocate(quadVertices, sizeof(quadVertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(2 * sizeof(GL_FLOAT)));

    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++){
            offsets[i*10 + j][0] = -1.0+0.1 + i*0.2;
            offsets[i*10 + j][1] = -1.0 + 0.1+ j*0.2;
        }

    // instanceVBO.reset(new QOpenGLBuffer);
    // instanceVBO->create();
    // instanceVBO->bind();
    // instanceVBO->allocate(offsets, sizeof(offsets));

    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
    // glVertexAttribDivisor(2, 1);
    shaderProgram->bind();
    for(int i=0; i< 100; i++){
        QString str = "offsets[" + QString::number(i) + "]";
        shaderProgram->setUniformValue(str.toStdString().c_str(), offsets[i]);
    }
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram->bind();
    VAO->bind();

    glDrawArraysInstanced(GL_TRIANGLES, 0 , 6, 100);
}
