#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_1_1>

class GLWidget : public QOpenGLWidget,
                 public QOpenGLFunctions_1_1
{
    Q_OBJECT
public:
    GLWidget();

protected:
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    virtual GLuint makeObject();

private:
    GLuint m_object = 0;
    GLdouble m_scale = 1.25;
    GLdouble m_xRot;
    GLdouble m_yRot;
    GLdouble m_zRot;
};

#endif // GLWIDGET_H
