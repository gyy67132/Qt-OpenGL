#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_1_1>


class GLWidget : public QOpenGLWidget ,  protected QOpenGLFunctions_1_1
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr){}
    ~GLWidget(){}

protected:
    void initializeGL() override
    {
        initializeOpenGLFunctions();
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    }

    void paintGL() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 0, 0);
        glPointSize(5);
        glBegin(GL_POINTS);
        glVertex2f(m_width / 2, m_height / 2);
        glEnd();
    }

    void resizeGL(int w, int h) override
    {
        m_width = w;
        m_height = h;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, w, h, 0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
    }

private:

    int m_width, m_height;

};
#endif // GLWIDGET_H
