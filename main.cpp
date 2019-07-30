#include "mainwindow.h"
#include "maindialog.h"
#include "jstojson.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    MainDialog d;
//    d.show();
    JSToJson db(&a);     //Change

    return a.exec();
}
