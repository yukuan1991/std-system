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
#include <QQuickWidget>
#include <QDebug>
#include <QMessageBox>
#include <LoginDialog.h>
#include <QUrl>

using namespace std::chrono_literals;
using namespace std::string_view_literals;


bool userVerification (const QString & user, const QString & pass, IoManipulator * io)
{
    auto data = io->doGet ("login");
    const auto list = data.toList ();

    for (auto & it : list)
    {
        const auto map = it.toMap ();
        if (map ["name"].toString () == user and map ["password"].toString () == pass)
        {
            return true;
        }
    }

    return false;
}

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

int main (int argc, char * argv[])
{
    QApplication app (argc, argv);

    set_style ();
    auto io = std::make_shared<HttpIoManipulator> ("127.0.0.1", 8080);
    io->setVideoIp ("127.0.0.1");
    io->setVideoPort (8080);

    while (1)
    {
        LoginDialog dlg;
        const auto res = dlg.exec ();

        if (res != QDialog::Accepted)
        {
            return 0;
        }

        const auto data = dlg.dump ().toMap ();
        if (userVerification (data ["user"].toString (), data ["pass"].toString (), io.get ()))
        {
            break;
        }
        QMessageBox::information (null, "登录", "用户名或密码错误");
    }

    StdMain m;

    m.setIoManipulator (io);
    m.resize (1366, 768);
    m.show ();

    return app.exec();
}
