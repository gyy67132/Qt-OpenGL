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

    float planeVertices[] = {
        // positions          // texture Coords
        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
        5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };

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

    shaderProgram.reset(new QOpenGLShaderProgram);
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":vertex.glsl");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":fragment.glsl");
    shaderProgram->link();

    vao.create();
    vao.bind();

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.allocate(planeVertices, sizeof(planeVertices));

    shaderProgram->bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));

    {
        vaoCube.create();
        vaoCube.bind();

        vertexBufferCube.create();
        vertexBufferCube.bind();
        vertexBufferCube.allocate(cubeVertices, sizeof(cubeVertices));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
    }

    model.setToIdentity();
    view.lookAt(QVector3D(0, 1, 4), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

    {
        texture.reset(new QOpenGLTexture(QOpenGLTexture::Target2D));
        QImage image(":metal.png");
        image.mirrored();
        texture->setSize(image.width(), image.height());
        if(image.hasAlphaChannel())
            texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
        else
            texture->setFormat(QOpenGLTexture::RGB8_UNorm);
        texture->allocateStorage();
        texture->setData(image);

        texture->setMinificationFilter(QOpenGLTexture::Linear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        texture->setWrapMode(QOpenGLTexture::Repeat);
    }

    {
        textureCube.reset(new QOpenGLTexture(QOpenGLTexture::Target2D));
        QImage image(":container.jpg");
        image.mirrored();
        textureCube->setSize(image.width(), image.height());
        textureCube->setFormat(QOpenGLTexture::RGB8_UNorm);
        textureCube->allocateStorage();
        textureCube->setData(image);
    }

    QOpenGLFramebufferObjectFormat fboFormat;
    fboFormat.setAttachment(QOpenGLFramebufferObject::Depth);
    fbo.reset(new QOpenGLFramebufferObject(this->size(), fboFormat));

    {
        // fboTexture.reset(new QOpenGLTexture(QOpenGLTexture::Target2D));
        // fboTexture->setSize(size().width(), size().height());
        // fboTexture->setFormat(QOpenGLTexture::RGBA8_UNorm);
        // fboTexture->allocateStorage();
        // fboTexture->setMinificationFilter(QOpenGLTexture::Linear);
        // fboTexture->setMagnificationFilter(QOpenGLTexture::Linear);
        // fboTexture->setWrapMode(QOpenGLTexture::ClampToEdge);
    }

    {
        float quadVertices[]={
            -1,-1, 0,0,
            1,-1, 1, 0,
            1,1, 1,1,

            -1,-1, 0,0,
            1,1, 1,1,
            -1,1,0,1
        };

        vaoQuad.create();
        vaoQuad.bind();
        vertexBufferQuad.create();
        vertexBufferQuad.bind();
        vertexBufferQuad.allocate(quadVertices, sizeof(quadVertices));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)(2*sizeof(GL_FLOAT)));

        shaderProgramQuad.reset(new QOpenGLShaderProgram);
        shaderProgramQuad->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":quadVertex.glsl");
        shaderProgramQuad->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":quadFragment.glsl");
        shaderProgramQuad->link();
    }
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    projection.setToIdentity();
    projection.perspective(45.0, static_cast<float>(w)/static_cast<float>(h), 0.1, 100);
}

void MyOpenGLWidget::paintGL()
{
    fbo->bind();
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.1, 1.0);

        glEnable(GL_DEPTH_TEST);

        shaderProgram->bind();
        vao.bind();
        texture->bind();

        shaderProgram->setUniformValue("model", model);
        shaderProgram->setUniformValue("view", view);
        shaderProgram->setUniformValue("projection", projection);
        shaderProgram->setUniformValue("texture", 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        shaderProgram->bind();
        vaoCube.bind();
        textureCube->bind();

        model.setToIdentity();
        model.translate(QVector3D(-1,0,-1));
        shaderProgram->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model.setToIdentity();
        model.translate(QVector3D(2,0,0));
        shaderProgram->setUniformValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    fbo->release();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    shaderProgramQuad->bind();
    shaderProgramQuad->setUniformValue("texture", 0);
    glBindTexture(GL_TEXTURE_2D, fbo->texture());
    vaoQuad.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void MyOpenGLWidget::changeShowState(int flag)
{

}
