#include "HttpIoManipulator.h"
#include <QVariant>
#include <base/io/net/conn_socket.hpp>
#include "tcp.h"
#include <QJsonDocument>
#include <QByteArray>
#include <base/utils/charset.hpp>
#include <QDebug>
#include <base/io/file/file.hpp>
#include <QStringList>
#include <base/io/file/file.hpp>
#include <QVariantList>

HttpIoManipulator::HttpIoManipulator(not_null<const char *> ip, uint16_t port)
    :ip_ (ip), port_ (port)
{

}

void HttpIoManipulator::sendForApproval(const QStringList &path, const QVariant &data)
{

}

QVariant HttpIoManipulator::pullData(const QString &data)
{
    const auto res = http_get (ip_, "/cgi-bin/pull-data", {{"type", data.toStdString ()}}, port_);
    QByteArray arr (res.data (), static_cast<int> (res.size ()));
    return QJsonDocument::fromJson (arr).toVariant ();
}

bool HttpIoManipulator::pushData (const QString &type, const QVariant &data)
{
    const auto res = http_post (ip_, ("/cgi-bin/push-data" + ("-" + type.toStdString ())).data (), QJsonDocument::fromVariant (data).toJson ().toStdString ());
    return not res.empty ();
}

bool HttpIoManipulator::addNode(const QStringList &path, const QString &name, const QString &dataFamily, const QString &dataType, const QVariant &data)
{
    QVariantMap map;

    QVariantList list;
    for (auto & it : path) { list.append (it); }

    map ["path"] = list;
    map ["file"] = dataFamily;
    map ["name"] = name;
    map ["data"] = data;
    map ["type"] = dataType;


    auto res = http_post (ip_, "/cgi-bin/add-node", QJsonDocument::fromVariant (map).toJson ().toStdString (), port_);
    qDebug () << res.data ();

    return res == "success";
}

bool HttpIoManipulator::delNode(const QStringList &path, const QString &dataFamily)
{
    QVariantMap map;

    QVariantList list;
    for (auto & it : path) { list.append (it); }

    map ["path"] = list;
    map ["file"] = dataFamily;

    file::write_buffer ("123.json", QJsonDocument::fromVariant (map).toJson ().toStdString ());

    auto res = http_post (ip_, "/cgi-bin/del-node", QJsonDocument::fromVariant (map).toJson ().toStdString (), port_);
    qDebug () << res.data ();
    return res == "success" ;
}

QVariant HttpIoManipulator::doPost(const QString &api, const QVariant &data)
{
    auto res = http_post (ip_, ("/cgi-bin/" + api).toStdString ().data (), QJsonDocument::fromVariant (data).toJson ().toStdString (), port_);
    return QJsonDocument::fromJson (QByteArray (res.data (), static_cast<int> (res.length ()))).toVariant ();
}
