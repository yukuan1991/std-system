#include "HttpIoManipulator.h"
#include <QVariant>
#include <base/io/net/conn_socket.hpp>
#include "tcp.h"
#include <QJsonDocument>
#include <QByteArray>
#include <base/utils/charset.hpp>
#include <QDebug>
#include <base/io/file/file.hpp>

HttpIoManipulator::HttpIoManipulator(not_null<const char *> ip, uint16_t port)
    :ip_ (ip), port_ (port)
{

}

void HttpIoManipulator::sendForApproval(const QStringList &path, const QVariant &data)
{

}

QVariant HttpIoManipulator::pullData(const QString &data)
{


//    const auto res = http_get (ip_, "/cgi-bin/pull-data", {{"type", binary_to_base64 (data.toStdString ())}}, port_);
//    qDebug () << __PRETTY_FUNCTION__ << " " << data;
//    qDebug () << res.data ();
//    QByteArray arr (res.data (), static_cast<int> (res.size ()));
//    return QJsonDocument::fromJson (arr).toVariant ();
    return {};
}

bool HttpIoManipulator::pushData (const QString &type, const QVariant &data)
{
//    qDebug () << data;
//    const auto res = http_post (ip_, ("/cgi-bin/push-data" + ("-" + type.toStdString ())).data (), QJsonDocument::fromVariant (data).toJson ().toStdString ());
//    qDebug () << res.data ();
//    return not res.empty ();
    return true;

}
