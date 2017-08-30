#include <QApplication>
#include <QQmlApplicationEngine>
#include "StdMain.h"
#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    StdMain w;
    w.show ();

    return app.exec();


    return app.exec();
}
