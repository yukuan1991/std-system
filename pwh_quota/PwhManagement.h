#ifndef PWHMANAGEMENT_H
#define PWHMANAGEMENT_H

#include <QWidget>
#include <memory>
#include "DetailedInfoTable.h"
#include <memory>
#include "IoManipulator.h"

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

    void setIoManipulator (std::shared_ptr<IoManipulator> io) { this->io = io; }
public:
    void on_button_detail_clicked();
    void on_button_modify_clicked();
    void on_button_addStdDatabase_clicked();
    void on_button_exportDF_clicked();
    void on_button_reportHeader_clicked();
    void initTreeWidget(const QVariant& data);
private:
    void onTreeWidgetClicked();
    void traverseTreeWidget(const QVariant& data, QVariantList& list);
private:
    Ui::PwhManagement *ui;
    std::shared_ptr<IoManipulator> io;
};

#endif // PWHMANAGEMENT_H
