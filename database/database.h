#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>
#include <QTableWidgetItem>
#include "IoManipulator.h"
#include <memory>

namespace Ui {
class database;
}

class database : public QWidget
{
    Q_OBJECT

public:
    explicit database(QWidget *parent = 0);
    ~database();
    void setIoManipulator (std::shared_ptr<IoManipulator> io) { this->io = io; }

    bool setTableHorizontalHeader(QStringList & list);
    bool setTabelRowCount(const int &value);
    bool setTabeltColumnCount(const int &value);
    bool setTableItemData(int &row , int &col , QTableWidgetItem *item);
    bool setTableItemIsEditable(const int &rowCount , const int &columnCount);
    void load(const QVariant &data);

    QVariant intiData();

    void showEvent (QShowEvent * event) override;
private:
    Ui::database *ui;
    std::shared_ptr<IoManipulator> io;
};

#endif // DATABASE_H
