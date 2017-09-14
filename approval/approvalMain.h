#ifndef APPROVALMAIN_H
#define APPROVALMAIN_H

#include <QWidget>
#include <QTableWidgetItem>
#include "IoManipulator.h"
#include <memory>

namespace Ui {
class approvalMain;
}

class approvalMain : public QWidget
{
    Q_OBJECT

public:
    explicit approvalMain(QWidget *parent = 0);
    ~approvalMain();

    void setIoManipulator (std::shared_ptr<IoManipulator> io) { this->io = io; }

    bool setTableHorizontalHeader(QStringList & list);
    bool setTabelRowCount(const int &value);
    bool setTabeltColumnCount(const int &value);
    bool setTableItemData(int &row , int &col , QTableWidgetItem *item);
    bool setTableItemIsEditable(const int &rowCount , const int &columnCount);
    void load(const QVariant &data);

    void showEvent (QShowEvent * event) override;

    void onClickAgreeButton();
    void onClickRefuseButton();

private:
    Ui::approvalMain *ui;
    std::shared_ptr<IoManipulator> io;
};

#endif // APPROVALMAIN_H
