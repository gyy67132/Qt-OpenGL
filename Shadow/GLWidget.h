#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>

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

        QOpenGLShader *vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
        if(!vertexShader->compileSourceFile(":/Vertex.glsl"))
        {
            qDebug()<<vertexShader->log();
            return;
        }

        QOpenGLShader *fragShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
        if(!fragShader->compileSourceFile(":/Fragment.glsl"))
        {
            qDebug()<<fragShader->log();
            return;
        }

        shaderProgram_common.addShader(vertexShader);
        shaderProgram_common.addShader(fragShader);

        shaderProgram_common.link();
        if(!shaderProgram_common.isLinked()){
            qDebug() << shaderProgram_common.log();
            return;
        }

        texture = new QOpenGLTexture(QImage(":/wood.png").mirrored());

        matrixPerspective.perspective(60, 800/600, 0.1, 100);

        QOpenGLShader* vertexShaderDepthmap = new QOpenGLShader(QOpenGLShader::Vertex, this);
        if(!vertexShaderDepthmap->compileSourceFile(":/Vertex_depthmap.glsl"))
        {
            qDebug()<<vertexShaderDepthmap->log();
            return;
        }

        QOpenGLShader* fragShaderDepthmap = new QOpenGLShader(QOpenGLShader::Fragment, this);
        if(!fragShaderDepthmap->compileSourceFile(":/Fragment_depthmap.glsl"))
        {
            qDebug()<<fragShaderDepthmap->log();
            return;
        }
        shaderProgram_depthmap.addShader(vertexShaderDepthmap);
        shaderProgram_depthmap.addShader(fragShaderDepthmap);
        shaderProgram_depthmap.link();
        if(!shaderProgram_depthmap.isLinked()){
            qDebug() << shaderProgram_depthmap.log();
            return;
        }

        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::NoAttachment);
        //format.setInternalTextureFormat(GL_DEPTH_COMPONENT32F);
        fbo = new QOpenGLFramebufferObject(size() , format);

        lightViewMatrix.lookAt(lightPos, QVector3D(0, 0, 0), QVector3D(0, 1, 0));
        lightMatrixOrtho.ortho(-10, 10, -10, 10, 0.1, 20);
    }
    virtual void resizeGL(int w, int h) override
    {
        Q_UNUSED(w);
        Q_UNUSED(h);
        glViewport(0,0,w,h);
    }
    virtual void paintGL() override
    {
        fbo->bind();

        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClearDepthf(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glViewport(0, 0, 640, 480);
        shaderProgram_depthmap.bind();
        shaderProgram_depthmap.setUniformValue("lightMatrix", lightMatrixOrtho * camera.viewMartix());
        renderScene(shaderProgram_depthmap);
        shaderProgram_depthmap.release();

        fbo->release();
        saveDepthMap(this, "./depth.png");

        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClearDepthf(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        //glViewport(0, 0, width(), height());
        //float* depthData = new float[size().width() * size().height()];
        //glReadPixels(0, 0, width(), height(), GL_DEPTH_COMPONENT, GL_FLOAT, depthData);
        //QImage image(depthData)//fbo->toImage(true, 0);
        //image.save("./depth.png");

        glViewport(0, 0, size().width(), size().height());
        shaderProgram_common.bind();
        texture->bind(0);
        shaderProgram_common.setUniformValue("texture1", 0);
        shaderProgram_common.setUniformValue("model", QMatrix4x4());
        shaderProgram_common.setUniformValue("matrix", matrixPerspective * camera.viewMartix());
        shaderProgram_common.setUniformValue("lightPos", lightPos);
        shaderProgram_common.setUniformValue("cameraPos", camera.cameraPos());
        renderScene(shaderProgram_common);
        shaderProgram_common.release();
    }

    void renderScene(QOpenGLShaderProgram& shaderProgram)
    {
        shaderProgram.bind();
        planVertexVbo.bind();
        shaderProgram.enableAttributeArray("pos");
        shaderProgram.setAttributeBuffer("pos", GL_FLOAT, 0, 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("normal");
        shaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("texcoord");
        shaderProgram.setAttributeBuffer("texcoord", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));

        glDrawArrays(GL_TRIANGLES, 0, 6);

        QMatrix4x4 matrixModel;
        matrixModel.translate(0, 1.5, 0);
        matrixModel.scale(0.5);
        renderCube(shaderProgram, matrixModel);

        matrixModel.setToIdentity();
        matrixModel.translate(2,0,1);
        matrixModel.scale(0.5);
        renderCube(shaderProgram, matrixModel);

        matrixModel.setToIdentity();
        matrixModel.translate(-1,0,2);
        matrixModel.rotate(60, 1,0,1);
        matrixModel.scale(0.25);
        renderCube(shaderProgram, matrixModel);
    }

    void renderCube(QOpenGLShaderProgram& shaderProgram,const QMatrix4x4& matrixModel)
    {
        cubeVertexVbo.bind();
        shaderProgram.enableAttributeArray("pos");
        shaderProgram.setAttributeBuffer("pos", GL_FLOAT, 0, 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("normal");
        shaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("texcoord");
        shaderProgram.setAttributeBuffer("texcoord", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));

        shaderProgram.setUniformValue("model", matrixModel );
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }



private:

private:
    QOpenGLBuffer planVertexVbo;
    QOpenGLBuffer cubeVertexVbo;
    QOpenGLShaderProgram shaderProgram_common;
    QOpenGLShaderProgram shaderProgram_depthmap;
    QOpenGLTexture *texture = nullptr;
    QMatrix4x4 matrixPerspective;
    QMatrix4x4 lightMatrixOrtho;
    Camera camera;
    bool pressed = false;
    QPoint lastPos;
    QVector3D lightPos = QVector3D(-2, 4, -1);
    QOpenGLFramebufferObject *fbo = nullptr;
    QMatrix4x4 lightViewMatrix;
    QOpenGLTexture *depthTexture = nullptr;

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

    void saveDepthMap(QOpenGLWidget* widget, const QString& outputPath) {
        // 获取窗口尺寸
        int width = 640;
        int height = 480;

        // 读取深度数据
        QVector<float> depthData(width * height);
        glReadPixels(0, 0, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, depthData.data());
        for(int i = 0; i<depthData.size();i++)
        {
            float t= depthData[i];
            if(qFabs(t) >= 0.00000001 && depthData[i] != 1 && qFabs(t) <= 0.9){
                float a = t;
                float b = a;
            }
        }
        // 转换为QImage
        QImage depthImage(width, height, QImage::Format_RGB888);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float depth = depthData[y * width + x];
                // 归一化深度值到[0, 255]
                int intensity = static_cast<int>(qBound(0.0f, depth, 1.0f) * 255.0f * 20);
                QRgb color = qRgb(intensity, intensity, intensity);
                depthImage.setPixel(x, height - 1 - y, color); // 垂直翻转
            }
        }

        // 保存图片
        if (!depthImage.save(outputPath)) {
            qDebug() << "保存深度图失败:" << outputPath;
        } else {
            qDebug() << "深度图已保存:" << outputPath;
        }
    }
};
#endif // GLWIDGET_H
