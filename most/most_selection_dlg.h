#ifndef MOST_SELECTION_DLG_H
#define MOST_SELECTION_DLG_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class most_selection_dlg;
}

class most_selection_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit most_selection_dlg(QWidget *parent = 0);
    ~most_selection_dlg();

    QString get_checked_item ();

private slots:
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::most_selection_dlg *ui;
};

#endif // MOST_SELECTION_DLG_H
