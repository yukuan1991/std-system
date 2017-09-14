#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantList>

class IoManipulator
{
public:
    explicit IoManipulator();

    IoManipulator (const IoManipulator &) = delete;
    IoManipulator (IoManipulator &&) = delete;
    void operator = (const IoManipulator &) = delete;
    void operator = (IoManipulator &&) = delete;

    virtual void sendForApproval (const QStringList & path, const QVariant & data) = 0;
    virtual bool addNode (const QStringList & path, const QString & name, const QString & dataFamily, const QString & dataType = "", const QVariant & data = QVariantList ()) = 0;
    virtual bool delNode (const QStringList & path, const QString & dataFamily) = 0;
    virtual bool pushData (const QString &, const QVariant &) = 0;
    virtual QVariant pullData (const QString &) = 0;
    virtual QVariant doPost (const QString & api, const QVariant & data) = 0;
    virtual QVariant doGet (const QString & api, const QVariantMap & data = {}) = 0;
    virtual QString videoPrefix () const = 0;
    virtual QString user () const { return "Krys"; }
    virtual void setUser (const QString & user) = 0;
    virtual bool uploadVideo (const std::string & path, const std::string & md5) = 0;
    virtual ~IoManipulator ();

};


