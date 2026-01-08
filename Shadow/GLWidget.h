#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QVector>
#include <QKeyEvent>
#include <QApplication>

#include "Camera.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget()
    {

    }

protected:
    virtual void initializeGL() override
    {
        initializeOpenGLFunctions();

        QVector<float> planeVertices = {
            // positions            // normals         // texcoords
            25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
            -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

            25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
            -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
            25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
        };

        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
            1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
            1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            // right face
            1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
            1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
            1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
            1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
            1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
            1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
            1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
            1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
        };


        planVertexVbo.create();
        planVertexVbo.bind();
        planVertexVbo.allocate(planeVertices.constData(), planeVertices.size() * sizeof(float));
        planVertexVbo.release();

        cubeVertexVbo.create();
        cubeVertexVbo.bind();
        cubeVertexVbo.allocate(vertices, sizeof(vertices));
        cubeVertexVbo.release();

        vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
        if(!vertexShader->compileSourceFile(":/Vertex.glsl"))
        {
            qDebug()<<vertexShader->log();
            return;
        }

        fragShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
        if(!fragShader->compileSourceFile(":/Fragment.glsl"))
        {
            qDebug()<<fragShader->log();
            return;
        }

        shaderProgram.addShader(vertexShader);
        shaderProgram.addShader(fragShader);

        shaderProgram.link();
        if(!shaderProgram.isLinked()){
            qDebug() << shaderProgram.log();
            return;
        }

        texture = new QOpenGLTexture(QImage(":/wood.png").mirrored());

        matrixPerspective.perspective(60, 800/600, 0.1, 100);
    }
    virtual void resizeGL(int w, int h) override
    {
        Q_UNUSED(w);
        Q_UNUSED(h);
        glViewport(0,0,w,h);
    }
    virtual void paintGL() override
    {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        shaderProgram.bind();
        planVertexVbo.bind();

        shaderProgram.enableAttributeArray("pos");
        shaderProgram.setAttributeBuffer("pos", GL_FLOAT, 0, 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("normal");
        shaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("texcoord");
        shaderProgram.setAttributeBuffer("texcoord", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));

        texture->bind(0);
        shaderProgram.setUniformValue("texture1", 0);

        shaderProgram.setUniformValue("model", QMatrix4x4());
        shaderProgram.setUniformValue("matrix", matrixPerspective * camera.viewMartix());
        shaderProgram.setUniformValue("lightPos", lightPos);
        shaderProgram.setUniformValue("cameraPos", camera.cameraPos());

        glDrawArrays(GL_TRIANGLES, 0, 6);

        QMatrix4x4 matrixModel;
        matrixModel.translate(0, 1.5, 0);
        matrixModel.scale(0.5);
        renderCube(matrixModel);

        matrixModel.setToIdentity();
        matrixModel.translate(2,0,1);
        matrixModel.scale(0.5);
        renderCube(matrixModel);

        matrixModel.setToIdentity();
        matrixModel.translate(-1,0,2);
        matrixModel.rotate(60, 1,0,1);
        matrixModel.scale(0.25);
        renderCube(matrixModel);
    }

    void renderCube(QMatrix4x4 matrixModel)
    {
        cubeVertexVbo.bind();
        shaderProgram.enableAttributeArray("pos");
        shaderProgram.setAttributeBuffer("pos", GL_FLOAT, 0, 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("normal");
        shaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("texcoord");
        shaderProgram.setAttributeBuffer("texcoord", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));

        //shaderProgram.setUniformValue("matrix", matrixPerspective * camera.viewMartix());
        shaderProgram.setUniformValue("model", matrixModel );
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }



private:
    QOpenGLBuffer planVertexVbo;
    QOpenGLBuffer cubeVertexVbo;
    QOpenGLShader *vertexShader = nullptr;
    QOpenGLShader *fragShader = nullptr;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLTexture *texture = nullptr;
    QMatrix4x4 matrixPerspective;
    Camera camera;
    bool pressed = false;
    QPoint lastPos;
    QVector3D lightPos = QVector3D(-2, 4, -1);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override
    {
        if(event->key() == Qt::Key_Down){
            camera.down();
        }else if(event->key() == Qt::Key_Up){
            camera.upward();
        }else if(event->key() == Qt::Key_Left){
            camera.left();
        }else if(event->key() == Qt::Key_Right){
            camera.towardsTheRight();
        }else if(event->key() == Qt::Key_Space){
            camera.restore();
        }else if(event->key() == Qt::Key_Escape){
            QApplication::quit();
        }else if(event->key() == Qt::Key_W){
            camera.forward();
        }else if(event->key() == Qt::Key_A){
            camera.left();
        }else if(event->key() == Qt::Key_S){
            camera.back();
        }else if(event->key() == Qt::Key_D){
            camera.towardsTheRight();
        }
        update();
        QWidget::keyPressEvent(event);
    }

    virtual void mousePressEvent(QMouseEvent *event) override
    {
        pressed = true;
        lastPos = event->pos();
        QWidget::mousePressEvent(event);
    }

    virtual void mouseReleaseEvent(QMouseEvent *event) override
    {
        pressed = false;
        QWidget::mouseReleaseEvent(event);
    }

    virtual void mouseMoveEvent(QMouseEvent *event) override
    {
        if(pressed){
            QPoint change = event->pos() - lastPos;
            camera.rotate(change.x(), change.y());
            lastPos = event->pos();
        }
        update();
        QWidget::mouseMoveEvent(event);
    }
};
#endif // GLWIDGET_H
