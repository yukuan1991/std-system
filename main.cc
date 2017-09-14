#include <QApplication>
#include <QQmlApplicationEngine>
#include "StdMain.h"
#include <QCoreApplication>
#include <base/io/file/file.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <boost/filesystem.hpp>
#include <boost/range/adaptors.hpp>
#include <HttpIoManipulator.h>
#include "utils/OpenTreeDialog.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

using namespace std::chrono_literals;
using namespace std::string_view_literals;

void set_style ()
{
    using namespace boost::filesystem;

    auto rng = boost::make_iterator_range (directory_iterator ("."), directory_iterator ());

    std::string qss;

    for (auto & it : rng)
    {
        if (it.path ().extension ().string () == ".css")
        {
            auto res = file::read_all (it.path ().string ().data ());
            if (res)
            {
                qss += res.value ();
            }
        }
    }

    qApp->setFont (QFont ("宋体", 11));
    qApp->setStyleSheet (QString::fromStdString (qss));
}

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);
    set_style ();
    StdMain w;
    w.setIoManipulator (std::make_shared<HttpIoManipulator> ("172.16.2.173",8080));
    w.resize (1366, 768);
    w.show ();

    return app.exec();
}
