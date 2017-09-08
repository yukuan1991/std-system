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
private:
    not_null<const char*> ip_;
    uint16_t port_;
};


