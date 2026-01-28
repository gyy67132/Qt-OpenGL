#include "GLWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    /*QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3,3);
    QSurfaceFormat::setDefaultFormat(format);*/

    QApplication a(argc, argv);
    GLWidget w;
    w.resize(800,600);
    w.show();
    return a.exec();
}
