#ifndef SPLITTERWIDGET_H
#define SPLITTERWIDGET_H

#include <QWidget>

class GLWidget;

class SplitterWidget : public QWidget
{
    Q_OBJECT
public:
    SplitterWidget(QWidget *parent = nullptr);

private slots:
    void rotateOneStep();
    void setCurrentGLWidget();

private:
    enum { NumRows = 2, NumColumns = 3};

    GLWidget *glWidgets[NumRows][NumColumns];
    GLWidget *currentGLWidget;
};

#endif // SPLITTERWIDGET_H
