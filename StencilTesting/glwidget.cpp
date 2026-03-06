#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setVersion(2, 1);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    setFormat(format);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    oldGL.reset(new QOpenGLFunctions_1_0);
    oldGL->initializeOpenGLFunctions();

    float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    float planeVertices[] = {
        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
        5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };

    planeVBO.create();
    planeVBO.bind();
    planeVBO.allocate(planeVertices, sizeof(planeVertices));

    cubeVBO.create();
    cubeVBO.bind();
    cubeVBO.allocate(cubeVertices, sizeof(cubeVertices));

    shaderProgram.reset(new QOpenGLShaderProgram);
    shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":vertex.glsl");
    shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":fragment.glsl");
    shaderProgram->link();
    shaderProgram->setUniformValue("textureIn", 0);

    shaderProgram_border.reset(new QOpenGLShaderProgram);
    shaderProgram_border->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":vertex.glsl");
    shaderProgram_border->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":fragment_border.glsl");
    shaderProgram_border->link();

    planeTexture.reset(new QOpenGLTexture(QOpenGLTexture::Target2D));
    QImage image(":/metal.png");
    image.mirrored();
    planeTexture->setSize(image.width(), image.height());
    planeTexture->setFormat(QOpenGLTexture::RGB8_UNorm);
    planeTexture->setData(image);

    cubeTexture.reset(new QOpenGLTexture(QOpenGLTexture::Target2D));
    QImage cubeImage(":marble");
    cubeImage.mirrored();
    cubeTexture->setSize(cubeImage.width(), cubeImage.height());
    cubeTexture->setFormat(QOpenGLTexture::RGB8_UNorm);
    cubeTexture->setData(cubeImage);

    //projection.frustum(-10.0, 10.0, -10.0, 10.0, 0.1, 10.0);
    model.setToIdentity();
    view.lookAt(QVector3D(0, 0, 3), QVector3D(0,0,0), QVector3D(0,1,0));
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    projection.setToIdentity();
    float fw = size().width();
    float fh = size().height();
    projection.perspective(70.0, fw / fh, 0.1, 100.0);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    shaderProgram->bind();
    planeTexture->bind();
    planeVBO.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
    model.setToIdentity();
    shaderProgram->setUniformValue("view", view);
    shaderProgram->setUniformValue("model", model);
    shaderProgram->setUniformValue("projection", projection);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glEnable(GL_STENCIL_TEST);//启动模版写入
    glStencilMask(0xFF);//设置模版掩码，写入的值都要与0xFF进行与运算
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // 是否通过模版测试，GL_ALWAYS是一直通过，1是比较值（模版里的值与1进行比较）
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    cubeVBO.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
    cubeTexture->bind();
    model.translate(QVector3D(-1, 0, -1));
    shaderProgram->setUniformValue("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);    

    model.setToIdentity();
    model.translate(QVector3D(2, 0, 0));
    shaderProgram->setUniformValue("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    shaderProgram->release();

    glDisable(GL_DEPTH_TEST);
    glStencilMask(0x00);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

    {
        shaderProgram_border->bind();

        model.setToIdentity();
        model.translate(-1, 0, -1);
        model.scale(1.1, 1.1, 1.1);
        shaderProgram_border->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model.setToIdentity();
        model.translate(2, 0, 0);
        model.scale(1.1, 1.1, 1.1);
        shaderProgram_border->setUniformValue("view", view);
        shaderProgram_border->setUniformValue("projection", projection);
        shaderProgram_border->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        shaderProgram_border->release();
    }


    oldGL->glMatrixMode(GL_MODELVIEW);
    oldGL->glLoadIdentity();
    oldGL->glColor3f(1.0, 0.0, 0.0);
    oldGL->glLineWidth(2.0);
    oldGL->glBegin(GL_LINES);
    oldGL->glVertex3f(0.0, 0.0, 0.0);
    oldGL->glVertex3f(1.0, 0.0, 0.0);
    oldGL->glVertex3f(0.0, 0.0, 0.0);
    oldGL->glVertex3f(0.0, 1.0, 0.0);
    oldGL->glEnd();
}
