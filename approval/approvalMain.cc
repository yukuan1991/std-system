#include "approvalMain.h"
#include "ui_approvalMain.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include "utils/Qt-Utils/openaf.h"
approvalMain::approvalMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::approvalMain)
{
    ui->setupUi(this);
    setTabeltColumnCount (6);
    QStringList header;
    header << "作业内容" << "基本时间" << "宽放率" << "标准时间" << "增值/非增值" << "操作分类";
    setTableHorizontalHeader (header);

    QVariantList list;
    list << "名称" << "类型";
    ui->treeWidget->setTreeHeader (list);

    connect (ui->treeWidget, &QTreeWidget::itemSelectionChanged, [this]
    {
        auto data = ui->treeWidget->currentSelectedData ();
        load(data);
    });
    connect (ui->agree, &QPushButton::clicked, this , &approvalMain::onClickAgreeButton);
    connect (ui->refuse, &QPushButton::clicked, this , &approvalMain::onClickRefuseButton);

}

approvalMain::~approvalMain()
{
    delete ui;
}

bool approvalMain::setTableHorizontalHeader(QStringList &list)
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

bool approvalMain::setTabelRowCount(const int &row)
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

bool approvalMain::setTabeltColumnCount(const int &col)
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

bool approvalMain::setTableItemData(int &row, int &col, QTableWidgetItem *item)
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

bool approvalMain::setTableItemIsEditable(const int &rowCount, const int &columnCount)
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

void approvalMain::load(const QVariant &data)
{
    auto map = data.toMap ();
    auto name = map["提交人"].toString();
    auto dest = map["提交到"].toString();
    auto type = map["类型"].toString();
    auto content = map["content"].toMap ();
    QVariantList table;
    if(dest == "standard")
    {
         table = content["table"].toList ();
    }
    else
    {
        if(type == "视频分析(试产)")
        {
            table = readVaf (content).toList ();
        }
        else if(type == "视频分析(量产)")
        {
            table = readVaf (content).toList ();
        }
        else if(type == "mtm")
        {
            table = readPts (content).toList ();
        }
        else if(type == "most")
        {
            table = readPts (content).toList ();
        }
        else if(type == "mod")
        {
            table = readPts (content).toList ();
        }

    }
    auto rowCount = table.size ();
    setTabelRowCount (rowCount);
    int row = 0;
    for(auto & it : table)
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
    ui->man_name->setText (name);
    ui->analysis_method->setText (type);
    ui->submit->setText (dest);
    setTableItemIsEditable(rowCount,6);
}

void approvalMain::showEvent(QShowEvent *event)
{
    QWidget::showEvent (event);
    if (io != null)
    {
        auto var = io->pullData ("approv");
        ui->treeWidget->setTreeData (var);
    }
}

void approvalMain::onClickRefuseButton()
{
    qDebug() << "refuse";
}

void approvalMain::onClickAgreeButton()
{
    qDebug() << "agree";
}
