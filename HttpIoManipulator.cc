#include "HttpIoManipulator.h"
#include <QVariant>
#include <base/io/net/conn_socket.hpp>
#include "tcp.h"
#include <QJsonDocument>
#include <QByteArray>
#include <base/utils/charset.hpp>

HttpIoManipulator::HttpIoManipulator(not_null<const char *> ip, uint16_t port)
    :ip_ (ip), port_ (port)
{

}

void HttpIoManipulator::sendForApproval(const QStringList &path, const QVariant &data)
{

}

QVariant HttpIoManipulator::pullData(const QString &data)
{
//    const auto res = http_get (ip_, port_, {{"type", data.toStdString ()}});
//    QByteArray arr (res.data (), static_cast<int> (res.size ()));
//    return QJsonDocument::fromJson (arr).toVariant ();
    return {};
}
