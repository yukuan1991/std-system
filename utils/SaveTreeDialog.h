#ifndef SAVETREEDIALOG_H
#define SAVETREEDIALOG_H

#include <QDialog>

namespace Ui {
class SaveTreeDialog;
}

class SaveTreeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveTreeDialog(QWidget *parent = 0);
    ~SaveTreeDialog();

    void load(const QVariant& data);
    QVariant dump() const;
private:
    void onButtonConfirmClicked();

private:
    Ui::SaveTreeDialog *ui;
};

#endif // SAVETREEDIALOG_H
