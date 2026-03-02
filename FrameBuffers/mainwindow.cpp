#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, &MainWindow::button_click , ui->openGLWidget, &MyOpenGLWidget::changeShowState);
    connect(ui->pushButton , &QPushButton::clicked , this, [=](){emit button_click(1);});
    connect(ui->pushButton_2 , &QPushButton::clicked , this, [=](){emit button_click(2);});
    connect(ui->pushButton_3 , &QPushButton::clicked , this, [=](){emit button_click(3);});
    connect(ui->pushButton_4 , &QPushButton::clicked , this, [=](){emit button_click(4);});
    connect(ui->pushButton_5 , &QPushButton::clicked , this, [=](){emit button_click(5);});
    connect(ui->pushButton_6 , &QPushButton::clicked , this, [=](){emit button_click(6);});
}

MainWindow::~MainWindow()
{
    delete ui;
}
