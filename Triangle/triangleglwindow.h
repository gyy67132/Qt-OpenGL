#ifndef TRIANGLEGLWINDOW_H
#define TRIANGLEGLWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions>

QT_FORWARD_DECLARE_CLASS(QOpenGLContext)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)


class TriangleGLWindow : public QWindow, protected QOpenGLFunctions
{
public:
    TriangleGLWindow(QWindow *parent = nullptr);
    ~TriangleGLWindow();

    void renderLater();

protected:
    bool event(QEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;
private:
    void initialize();

private:
    void render();

private:
    QOpenGLContext *m_context = nullptr;
    QOpenGLShaderProgram *m_program = nullptr;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    int m_frame = 0;
};

#endif // TRIANGLEGLWINDOW_H
