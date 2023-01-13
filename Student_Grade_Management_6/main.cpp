#include "mainwindow.h"
#include<login.h>
#include <QApplication>
#include<QDir>
#include<QDateTime>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(a.applicationDirPath());


    MainWindow w;


    return a.exec();
}
