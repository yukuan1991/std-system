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
#include <HttpIoManipulator.h>
#include "utils/SaveTreeDialog.h"
#include <QFile>
#include <QJsonDocument>
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
//    w.setIoManipulator (std::make_shared<HttpIoManipulator> ("172.16.5.81", 8080));
//    w.resize (1366, 768);
//    w.show ();

    QFile file ("1.json");
    file.open (QFile::ReadOnly);
    const auto arr = file.readAll ();
    const auto text = QJsonDocument::fromJson(arr).toVariant();

    SaveTreeDialog w;
    w.load(text);
    if(QDialog::Accepted == w.exec())
    {
        auto data = w.dump();
        const auto list = data.toMap()["path"].toList();
        for(int i = 0; i < list.size(); i++)
        {
            qDebug() << list.at(i).toString();
        }
        qDebug() << data.toMap()["name"];
    }


    return app.exec();
}
