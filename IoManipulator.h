#pragma once

#include <QObject>

class IoManipulator
{
public:
    explicit IoManipulator();

    IoManipulator (const IoManipulator &) = delete;
    IoManipulator (IoManipulator &&) = delete;
    void operator = (const IoManipulator &) = delete;
    void operator = (IoManipulator &&) = delete;

    virtual void sendForApproval (const QStringList & path, const QVariant & data) = 0;
    virtual bool pushData (const QString &, const QVariant &) = 0;
    virtual QVariant pullData (const QString &) = 0;
    virtual ~IoManipulator ();

};


