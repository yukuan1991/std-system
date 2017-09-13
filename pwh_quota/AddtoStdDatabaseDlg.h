#ifndef ADDTOSTDDATABASEDLG_H
#define ADDTOSTDDATABASEDLG_H

#include <QDialog>

namespace Ui {
class AddtoStdDatabaseDlg;
}

class AddtoStdDatabaseDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddtoStdDatabaseDlg(QWidget *parent = 0);
    ~AddtoStdDatabaseDlg();

    void load(const QVariant& data);
    QVariant dump () const;

    void onCheckAllStateChanged(int state);
    void onButtonConfirmClicked();

private:
    Ui::AddtoStdDatabaseDlg *ui;
};

#endif // ADDTOSTDDATABASEDLG_H
