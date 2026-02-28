#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, &MainWindow::button_click , ui->openGLWidget, &MyOpenGLWidget::changeShowState);
    connect(ui->pushButton , &QPushButton::clicked , this, [=](){emit button_click(0);});
}

MainWindow::~MainWindow()
{
    delete ui;
}
