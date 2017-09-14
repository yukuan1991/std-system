#pragma once
#include "IoManipulator.h"
#include <base/lang/not_null.h>


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
    virtual QString user () const override;
    virtual void setUser (const QString & user) override;

private:
    not_null<const char*> ip_;
    uint16_t port_;
    QString user_;
};


