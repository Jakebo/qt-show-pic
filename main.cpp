#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QLabel>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowFullScreen);
    w.show();

    return a.exec();
}
