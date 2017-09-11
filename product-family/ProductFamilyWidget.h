#ifndef PRODUCTFAMILYWIDGET_H
#define PRODUCTFAMILYWIDGET_H

#include <QWidget>
#include <memory>
#include "IoManipulator.h"

namespace Ui {
class ProductFamilyWidget;
}

class ProductFamilyWidget : public QWidget
{
    Q_OBJECT
signals:
    void add(const QStringList&, const QString&);
    void remove(const QStringList&);
    void modify(const QStringList&, const QStringList&);
public:
    explicit ProductFamilyWidget(QWidget *parent = 0);
    ~ProductFamilyWidget();
    void setIoManipulator (std::shared_ptr<IoManipulator> io) { this->io = io; }
private:
    void showEvent (QShowEvent * event) override;
    void initConn ();
    void onAddButtonClicked ();
    void onRemoveButtonClicked ();
    void onModifyButtonClicked ();
    void onAdd (const QStringList & list, const QString & name);
    void onDel (const QStringList & list);
private:
    Ui::ProductFamilyWidget *ui;
    std::shared_ptr<IoManipulator> io;
};

#endif // PRODUCTFAMILYWIDGET_H
