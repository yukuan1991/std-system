#include "database.h"
#include "ui_database.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

database::database(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::database)
{
    ui->setupUi(this);
    setTabeltColumnCount (6);
    QStringList header;
    header << "作业内容" << "基本时间" << "宽放率" << "标准时间" << "增值/非增值" << "操作分类";
    setTableHorizontalHeader (header);

//    auto value = intiData ();
//    load (value);

//    auto data = ui->treeWidget->currentSelectedData ();
//    qDebug() << data;

    QVariantList list;
    list << "名称" << "类型";
    ui->treeWidget->setTreeHeader (list);

    connect (ui->treeWidget, &QTreeWidget::itemSelectionChanged, [this]
    {
        auto data = ui->treeWidget->currentSelectedData ();
        qDebug() << QJsonDocument::fromVariant (data).toJson ().toStdString ().data ();
        load(data);
    });
}

database::~database()
{
    delete ui;
}

bool database::setTableHorizontalHeader(QStringList &list)
{
    if(list.empty ())
    {
        return false;
    }
    else
    {
        ui->tableWidget->setHorizontalHeaderLabels (list);
        return true;
    }
}

bool database::setTabeltColumnCount(const int &col)
{
    if(col <= 0)
    {
        return false;
    }
    else
    {
        ui->tableWidget->setColumnCount (col);
        return true;
    }
}

bool database::setTableItemData(int &row, int &col, QTableWidgetItem *item)
{
    if(row <= 0 or col <= 0)
    {
        return false;
    }
    else
    {
        ui->tableWidget->setItem(row, col, item);
        return true;
    }
}

bool database::setTableItemIsEditable(const int &rowCount, const int &columnCount)
{
    bool flag = false;
    if(rowCount <= 0 or columnCount <= 0)
    {
        return flag;
    }
    else
    {
        for(int col = 1; col < columnCount; col++)
        {
            for(int row = 0; row < rowCount; row++)
            {
                QTableWidgetItem *item = ui->tableWidget->item (row,col);

                if(item) {
                    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
                } else {
                    item = new QTableWidgetItem;
                    item->setFlags(item->flags() & (~Qt::ItemIsEditable));
                    ui->tableWidget->setItem(row, col, item);

                }
            }
        }
        flag = true;
    }
    return flag;
}

void database::load(const QVariant &data)
{
    auto content = data.toMap ()["content"].toMap ();
    auto tabel = content["table"].toList ();
 //   auto videoAdd = video["videoAdd"].toString ();
 //   ui->video_add->setText (videoAdd);

    auto rowCount = tabel.size ();
    setTabelRowCount (rowCount);
    int row = 0;
    for(auto & it : tabel)
    {
        auto jobContent = it.toMap()["作业内容"].toString();
        auto basicTime = it.toMap ()["基本时间"].toString();
        auto zengzhi = it.toMap ()["增值/非增值"].toString();
        auto kuanfang = it.toMap ()["宽放率"].toString();
        auto caozuo = it.toMap ()["操作分类"].toString();
        auto biaozhun = it.toMap ()["标准时间"].toString();
        QTableWidgetItem *newItem = new QTableWidgetItem(jobContent);
        ui->tableWidget->setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(basicTime);
        ui->tableWidget->setItem(row, 1, newItem);
        newItem = new QTableWidgetItem(kuanfang);
        ui->tableWidget->setItem(row, 2, newItem);
        newItem = new QTableWidgetItem(biaozhun);
        ui->tableWidget->setItem(row, 3, newItem);
        newItem = new QTableWidgetItem(zengzhi);
        ui->tableWidget->setItem(row, 4, newItem);
        newItem = new QTableWidgetItem(caozuo);
        ui->tableWidget->setItem(row, 5, newItem);
        row++;
    }
    setTableItemIsEditable(rowCount,6);
}

QVariant database::intiData()
{

    QVariantMap video;
    video["videoAdd"] = "fadfadfadfadfa";

    QVariantList list;

    QVariantMap map1;
    map1["公司内部代码"] = "fadfadf";
    map1["作业内容"] = "fadfadf";
    map1["基本时间"] = "fadfadf";
    map1["历史来源"] = "fadfadf";
    map1["总编码"] = "fadfadf";
    map1["开始时间"] = "fadfadf";
    map1["结束时间"] = "fadfadf";
    list.push_back (map1);

    QVariantMap map2;

    map2["公司内部代码"] = "ffa";
    map2["作业内容"] = "z";
    map2["基本时间"] = "zcx";
    map2["历史来源"] = "fadfadf";
    map2["总编码"] = "kjk";
    map2["开始时间"] = "iyu";
    map2["结束时间"] = "jmbnm";
    list.push_back (map2);


    QVariantMap totalMap;

    totalMap ["video"] = video;
    totalMap["list"] = list;

    QVariantMap form;
    form["form"] = totalMap;

    return form;
}

void database::showEvent(QShowEvent *event)
{
    QWidget::showEvent (event);
    if (io != null)
    {
        auto var = io->pullData ("standard");
        ui->treeWidget->setTreeData (var);
    }

}

bool database::setTabelRowCount(const int &row)
{
    if(row <= 0)
    {
        return false;
    }
    else
    {
        ui->tableWidget->setRowCount (row);
        return true;
    }
}
