#ifndef PWHMANAGEMENT_H
#define PWHMANAGEMENT_H

#include <QWidget>
#include <memory>
#include "DetailedInfoTable.h"

namespace Ui {
class PwhManagement;
}

class QLabel;
class PwhManagement : public QWidget
{
    Q_OBJECT

public:
    explicit PwhManagement(QWidget *parent = 0);
    ~PwhManagement();
public:
    void on_button_detail_clicked();
    void on_button_modify_clicked();
    void on_button_addStdDatabase_clicked();
    void on_button_exportDF_clicked();
    void on_button_reportHeader_clicked();
    void initTreeWidget(const QVariant& data);
private:
    Ui::PwhManagement *ui;
};

#endif // PWHMANAGEMENT_H
