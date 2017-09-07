#pragma once

#include <QObject>

class IoManipulator
{
public:
    explicit IoManipulator();
    virtual void sendForApproval (const QStringList & path, const QVariant & data) = 0;
    virtual QVariant pullData (const QString &) = 0;
    virtual ~IoManipulator ();
};


