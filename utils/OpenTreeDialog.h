#ifndef OPENTREEDIALOG_H
#define OPENTREEDIALOG_H

#include <QDialog>

namespace Ui {
class OpenTreeDialog;
}

class OpenTreeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenTreeDialog(QWidget *parent = 0);
    ~OpenTreeDialog();

    void load(const QVariant& data);
    QVariant dump();

private:
    Ui::OpenTreeDialog *ui;
};

#endif // OPENTREEDIALOG_H
