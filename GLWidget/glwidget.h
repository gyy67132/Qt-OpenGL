#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    ~GLWidget();

    void setClearColor(const QColor &color);
    void rotateBy(int xAngle, int yAngle, int zAngle);

signals:
    void clicked();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void makeObject();

    QColor clearColor = Qt::black;
    int xRot = 0;
    int yRot = 0;
    int zRot = 0;

    QOpenGLTexture *textures[6]={nullptr};
    QOpenGLBuffer vbo;
    QOpenGLShaderProgram *program = nullptr;
};

#endif // GLWIDGET_H
