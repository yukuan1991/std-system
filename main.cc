#include <QApplication>
#include <QQmlApplicationEngine>
#include "StdMain.h"
#include <QCoreApplication>
#include <base/io/file/file.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <boost/filesystem.hpp>
#include <boost/range/adaptors.hpp>

#include "video/VideoMainTrial.h"
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
    app.setAttribute (Qt::AA_DontCreateNativeWidgetSiblings, true);
    set_style ();
//    StdMain w;
//    w.resize (1366, 768);
//    w.show ();
    VideoMainTrial w;
    w.show();

    return app.exec();
}
