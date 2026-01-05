#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QVector>

class Camera{
    Camera(QVector3D eye, QVector3D center, QVector3D up);
};

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget()
    {
        //QSurfaceFormat format;
        //format.setVersion(4,3);
        //setFormat(format);
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

        const char vertexShaderString [] =
            "attribute highp vec4 pos;\n"
            "attribute lowp vec4 normal;\n"
            "attribute lowp vec4 texcoord;\n"
            "uniform highp mat4 matrix;\n"
            "varying mediump vec4 outTexc;\n"
            "void main(){\n"
            "  gl_Position =  matrix * pos;\n"
            "  outTexc = texcoord;\n"
            "}\n";
        const char fragmentShaderString [] =
            "varying mediump vec4 outTexc;\n"
            "uniform sampler2D texture;\n"
            "void main(){\n"
            "  gl_FragColor = texture2D(texture, outTexc.st);\n"
            "}\n";

        vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
        if(!vertexShader->compileSourceCode(vertexShaderString))
        {
            qDebug()<<vertexShader->log();
            return;
        }

        fragShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
        if(!fragShader->compileSourceCode(fragmentShaderString))
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
    }
    virtual void resizeGL(int w, int h) override
    {
        Q_UNUSED(w);
        Q_UNUSED(h);
        glViewport(0,0,w,h);
    }
    virtual void paintGL() override
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.bind();
        planVertexVbo.bind();

        shaderProgram.enableAttributeArray("pos");
        shaderProgram.setAttributeBuffer("pos", GL_FLOAT, 0, 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("normal");
        shaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("texcoord");
        shaderProgram.setAttributeBuffer("texcoord", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));

        texture->bind(0);
        shaderProgram.setUniformValue("texture", 0);
        QMatrix4x4 m;
        m.translate(0,0,-3);

        QMatrix4x4 m2;
        m2.perspective(60, 800/600, 0.1, 100);
        shaderProgram.setUniformValue("matrix", m2 * m);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        //shaderProgram.bind();
        cubeVertexVbo.bind();
        shaderProgram.enableAttributeArray("pos");
        shaderProgram.setAttributeBuffer("pos", GL_FLOAT, 0, 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("normal");
        shaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
        shaderProgram.enableAttributeArray("texcoord");
        shaderProgram.setAttributeBuffer("texcoord", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));

        //texture->bind(0);
        //shaderProgram.setUniformValue("texture", 0);

        QMatrix4x4 m3;
        m3.translate(0,0,-3);

        QMatrix4x4 m4;
        m4.perspective(60, 800/600, 0.1, 100);

        QMatrix4x4 m5;
        m5.translate(0, 1.5, 0);
        m5.scale(0.5);
        shaderProgram.setUniformValue("matrix", m4 * m3 * m5 );
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

private:

    QOpenGLBuffer planVertexVbo;
    QOpenGLBuffer cubeVertexVbo;
    QOpenGLShader *vertexShader = nullptr;
    QOpenGLShader *fragShader = nullptr;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLTexture *texture = nullptr;
};
#endif // GLWIDGET_H
