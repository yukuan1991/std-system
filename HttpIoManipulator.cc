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
    Q_UNUSED(path);
    Q_UNUSED(data);
}

QVariant HttpIoManipulator::pullData(const QString &data)
{
    const auto res = http_get (ip_.data (), "/cgi-bin/pull-data", {{"type", data.toStdString ()}}, port_);
    QByteArray arr (res.data (), static_cast<int> (res.size ()));
    return QJsonDocument::fromJson (arr).toVariant ();
}

bool HttpIoManipulator::pushData (const QString &type, const QVariant &data)
{
    const auto res = http_post (ip_.data (), ("/cgi-bin/push-data" + ("-" + type.toStdString ())).data (), QJsonDocument::fromVariant (data).toJson ().toStdString ());
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


    auto res = http_post (ip_.data (), "/cgi-bin/add-node", QJsonDocument::fromVariant (map).toJson ().toStdString (), port_);
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

    auto res = http_post (ip_.data (), "/cgi-bin/del-node", QJsonDocument::fromVariant (map).toJson ().toStdString (), port_);
    qDebug () << res.data ();
    return res == "success";
}

QVariant HttpIoManipulator::doPost(const QString &api, const QVariant &data)
{
    auto res = http_post (ip_.data (), ("/cgi-bin/" + api).toStdString ().data (), QJsonDocument::fromVariant (data).toJson ().toStdString (), port_);
    return QJsonDocument::fromJson (QByteArray (res.data (), static_cast<int> (res.length ()))).toVariant ();
}

QVariant HttpIoManipulator::doGet(const QString &api, const QVariantMap &data)
{
    Q_UNUSED (data);
    const auto res = http_get (ip_.data (), ("/cgi-bin/" + api).toStdString ().data (), {}, port_);

    return QJsonDocument::fromJson (QByteArray (res.data (), static_cast<int> (res.length ()))).toVariant ();
}

QString HttpIoManipulator::user() const
{
    return user_;
}

void HttpIoManipulator::setUser(const QString &user)
{
    user_ = user;
}

QString HttpIoManipulator::videoPrefix() const
{
    return ("http://" + videoIp_ + ":" + std::to_string (videoPort_) + "/videos/").data ();
}

bool HttpIoManipulator::uploadVideo(const std::string &bin, const std::string & md5)
{
    auto sock = conn_socket::make_socket ();
    sock.connect (videoIp_.data (), 1024);

    const auto len = bin.size ();
    const auto htonl_len = htonl (len);

    sock.writen (htonl_len);
    sock.writen (md5);
    std::array<char, 1> reply;
    sock.readn (reply);

    if (reply.at (0) == 1)
    {
        return true;
    }

    if (sock.writen (bin) != bin.size ())
    {
        return false;
    }
    else
    {
        return true;
    }

}
