#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class database;
}

class database : public QWidget
{
    Q_OBJECT

public:
    explicit database(QWidget *parent = 0);
    ~database();

    bool setTableHorizontalHeader(QStringList & list);
    bool setTabelRowCount(const int &value);
    bool setTabeltColumnCount(const int &value);
    bool setTableItemData(int &row , int &col , QTableWidgetItem *item);
    bool setTableItemIsEditable(const int &rowCount , const int &columnCount);
    void load(const QVariant &data);

    QVariant intiData();
private:
    Ui::database *ui;
};

#endif // DATABASE_H
