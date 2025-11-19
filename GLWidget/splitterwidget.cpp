#include <QtWidgets>
#include "splitterwidget.h"

#include "glwidget.h"

SplitterWidget::SplitterWidget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;

    for(int i = 0; i < NumRows; ++i)
        for(int j = 0; j < NumColumns; ++j){
            QColor clearColor;
            clearColor.setHsv(((i * NumRows) + j) * 255 / (NumRows * NumColumns - 1), 255 ,63);

            glWidgets[i][j] = new GLWidget;
            glWidgets[i][j]->setClearColor(clearColor);
            glWidgets[i][j]->rotateBy(42*16, 42*16, -21*16);
            mainLayout->addWidget(glWidgets[i][j], i, j);

            connect(glWidgets[i][j], &GLWidget::clicked, this, &SplitterWidget::setCurrentGLWidget);
        }
    setLayout(mainLayout);

    currentGLWidget = glWidgets[0][0] ;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SplitterWidget::rotateOneStep);
    timer->start(20);


}

void SplitterWidget::setCurrentGLWidget()
{
    currentGLWidget = qobject_cast<GLWidget*>(sender());
}

void SplitterWidget::rotateOneStep()
{
    if(currentGLWidget)
        currentGLWidget->rotateBy(2 * 16, 2 * 16, -1 * 16);
}
