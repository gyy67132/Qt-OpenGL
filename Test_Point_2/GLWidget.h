#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr)
    {

    }
    ~GLWidget(){}
protected:
    virtual void initializeGL() override
    {
        initializeOpenGLFunctions();
        glEnable(GL_PROGRAM_POINT_SIZE);
        const char *vertexString =
            "#version 330 core\n"
            "layout(location = 0) in vec3 aPos;"
            "void main(){"
            "gl_Position = vec4(aPos, 1.0);"
            "gl_PointSize  = 5.0;  "
            "}";
        QOpenGLShader vertexShader(QOpenGLShader::Vertex);
        if(!vertexShader.compileSourceCode(vertexString)){
            qCritical() << "Vertex Compile Error:" << vertexShader.log();
        }

        const char *fragmentString =
            "#version 330 core\n"
            "out vec4 FragColor;"
            "void main(){"
            "FragColor = vec4(1.0,0.0,0.0,1.0);"
            "}";
        QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
        if(!fragmentShader.compileSourceCode(fragmentString)){
            qCritical() << "Fragment Compile Error:" << fragmentShader.log();
        }

        shaderProgram.addShader(&vertexShader);
        shaderProgram.addShader(&fragmentShader);
        bool ret = shaderProgram.link();

        VAO.create();
        VAO.bind();
        VBO.create();
        VBO.bind();
        float vertices[] = {0.0, 0.0, 0.0};
        VBO.allocate(vertices, sizeof(vertices));

        shaderProgram.enableAttributeArray(0);
        shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);

        glClearColor(1, 1, 1, 1);

    }
    virtual void resizeGL(int w, int h) override
    {
        Q_UNUSED(w);
        Q_UNUSED(h);
    }
    virtual void paintGL() override
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.bind();
        VAO.bind();
        glDrawArrays(GL_POINTS, 0, 1);
        VAO.release();
        shaderProgram.release();
    }
private:
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer VBO;
    QOpenGLVertexArrayObject VAO;
};
#endif // GLWIDGET_H
