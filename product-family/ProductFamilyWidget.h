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
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    void showEvent (QShowEvent * event) override;
    void initConn ();
    void onAddButtonClicked ();
    void onRemoveButtonClicked ();
    void onModifyButtonClicked ();
    void onAdd (const QStringList & list, const QString & name);
    QVariant refreshVariant(QStringList & list, const QString &name, const QVariant var);
private:
    Ui::ProductFamilyWidget *ui;
    std::shared_ptr<IoManipulator> io;
};

#endif // PRODUCTFAMILYWIDGET_H
