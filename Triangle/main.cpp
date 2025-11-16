#include "mainwindow.h"
#include "triangleglwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    TriangleGLWindow w;
    w.resize(640, 480);
    w.show();
    w.renderLater();
    return a.exec();
}
