#include "database.h"
#include "ui_database.h"
#include <QFile>
#include <QJsonDocument>

database::database(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::database)
{
    ui->setupUi(this);
    setTabeltColumnCount (5);
    QStringList header;
    header << "公司内部代码" << "标准操作单元作业内容" << "标准操作单元基本时间" << "历史来源" << "预定工时法总编码";
    setTableHorizontalHeader (header);

    auto value = intiData ();
    load (value);

    QVariantList list;
    list << "名称" << "类型";
    ui->treeWidget->setTreeHeader (list);
    QFile file ("database/test.json");
    file.open (QFile::ReadOnly);
    const auto arr = file.readAll ();
    ui->treeWidget->setTreeData (QJsonDocument::fromJson (arr).toVariant ());
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
    auto form = data.toMap ()["form"].toMap ();
    auto video = form["video"].toMap ();
    auto videoAdd = video["videoAdd"].toString ();
 //   ui->video_add->setText (videoAdd);

    auto list = form["list"].toList ();
    auto rowCount = list.size ();
    setTabelRowCount (rowCount);
    int row = 0;
    for(auto & it : list)
    {
        auto companyInternalCode = it.toMap ()["公司内部代码"].toString();
        auto jobContent = it.toMap()["作业内容"].toString();
        auto basicTime = it.toMap ()["基本时间"].toString();
        auto historicalOrigin = it.toMap ()["历史来源"].toString();
        auto allCode = it.toMap ()["总编码"].toString();
        auto startTime = it.toMap ()["开始时间"].toString();
        auto stopTime = it.toMap ()["结束时间"].toString();
        QTableWidgetItem *newItem = new QTableWidgetItem(companyInternalCode);
        ui->tableWidget->setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(jobContent);
        ui->tableWidget->setItem(row, 1, newItem);
        newItem = new QTableWidgetItem(basicTime);
        ui->tableWidget->setItem(row, 2, newItem);
        newItem = new QTableWidgetItem(historicalOrigin);
        ui->tableWidget->setItem(row, 3, newItem);
        newItem = new QTableWidgetItem(allCode);
        ui->tableWidget->setItem(row, 4, newItem);
        row++;
    }
    setTableItemIsEditable(rowCount,5);
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
