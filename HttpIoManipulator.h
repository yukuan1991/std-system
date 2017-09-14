#pragma once
#include "IoManipulator.h"
#include <base/lang/not_null.h>
#include <base/lang/move.hpp>


class HttpIoManipulator : public IoManipulator
{
public:
    HttpIoManipulator(not_null<const char*> ip, uint16_t port = 80);
    void sendForApproval (const QStringList & path, const QVariant & data) override;
    QVariant pullData (const QString & type) override;
    bool pushData (const QString & type, const QVariant & data) override;
    bool addNode (const QStringList & path, const QString & name, const QString & dataFamily, const QString & dataType, const QVariant & data) override;
    bool delNode (const QStringList & path, const QString & dataFamily) override;
    QVariant doPost (const QString & api, const QVariant & data) override;
    QVariant doGet (const QString & api, const QVariantMap & data) override;
    QString user () const override;
    void setUser (const QString & user) override;
    QString videoPrefix () const override;
    void setVideoIp (std::string ip) { videoIp_ = ::move (ip); }
    bool uploadVideo (const std::string & path, const std::string & md5) override;
    void setVideoPort (uint16_t videoPort) { videoPort_ = videoPort; }

private:
    std::string ip_;
    uint16_t port_;
    uint16_t videoPort_;
    QString user_;
    std::string videoIp_;
};


