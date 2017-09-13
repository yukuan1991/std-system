#ifndef MODIFYPRODUCTDLG_H
#define MODIFYPRODUCTDLG_H

#include <QDialog>
#include <QVariantMap>

namespace Ui {
class ModifyProductDlg;
}

class ModifyProductDlg : public QDialog
{
    Q_OBJECT
public:
    explicit ModifyProductDlg(QWidget *parent = 0);
    ~ModifyProductDlg();

    void load(const QVariant& data);
    QVariant dump();

private:
    Ui::ModifyProductDlg *ui;
};

#endif // MODIFYPRODUCTDLG_H
