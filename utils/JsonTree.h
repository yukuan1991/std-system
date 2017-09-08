#pragma once
#include <QTreeWidget>
#include <base/lang/not_null.h>
#include <memory>


class JsonTree : public QTreeWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant treeData READ treeData WRITE setTreeData NOTIFY treeDataChanged MEMBER treeData_)
    Q_PROPERTY(QVariant treeHeader READ treeHeader WRITE setTreeHeader NOTIFY treeHeaderChanged MEMBER treeHeader_)
signals:
    void treeDataChanged (const QVariant &);
    void treeHeaderChanged (const QVariant &);
    void itemElaborator (QTreeWidgetItem*);
    void add(const QStringList&, const QString&);
    void remove(const QStringList&);
    void modify(const QStringList&, const QStringList&);
public:
    JsonTree(QWidget * parent = null);
    QVariant treeData () const noexcept { return treeData_; }

    void setTreeData (const QVariant & data) { treeData_ = data; emit treeDataChanged (treeData_); }
    QVariant currentSelectedData () const;

    void setTreeHeader (const QVariant & headers) { treeHeader_ = headers; emit treeHeaderChanged (treeHeader_); }
    QVariant treeHeader () const noexcept { return treeHeader_; }

    ~JsonTree () override;

private:
    void resetHeader ();
    void resetTree ();

    std::unique_ptr<QTreeWidgetItem> setupItem (const QVariant & data);
    std::unique_ptr<QTreeWidgetItem> setupItem (const QVariantList & data);
    std::unique_ptr<QTreeWidgetItem> setupItem (const QVariantMap & data);
private:
    QVariant treeData_;
    QVariant treeHeader_;
};


