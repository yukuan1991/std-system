#include "ReportTableWidget.h"
#include "ui_ReportTableWidget.h"

ReportTableWidget::ReportTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportTableWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QVariantMap totalMap;

    QVariantList list;
    QVariantMap map1;
    map1["作业内容"] = "焊锡";
    map1["基本时间"] = 0.1;
    map1["宽放率"] = "0.00%";
    map1["标准时间"] = 0.1;
    map1["增值/非增值"] = "增值";
    map1["操作分类"] = "加工";

    QVariantMap map2;
    map2["作业内容"] = "xxx";
    map2["基本时间"] = 0.2;
    map2["宽放率"] = "0.00%";
    map2["标准时间"] = 0.2;
    map2["增值/非增值"] = "非增值";
    map2["操作分类"] = "搬运";

    QVariantMap map3;
    map3["作业内容"] = "sdd";
    map3["基本时间"] = 0.3;
    map3["宽放率"] = "0.00%";
    map3["标准时间"] = 0.3;
    map3["增值/非增值"] = "增值";
    map3["操作分类"] = "加工";

    list << map1 << map2 << map3;

    totalMap["table"] = list;
    load(totalMap);
}

ReportTableWidget::~ReportTableWidget()
{
    delete ui;
}

QVariant ReportTableWidget::dump()
{
    const auto rows = ui->tableWidget->rowCount();
    const auto columns = ui->tableWidget->columnCount();
    if(rows == 0 or columns == 0)
    {
        return QVariant{};
    }

    QVariantList tableList;
    for(int i = 0; i < rows; i++)
    {
        QVariantMap map;
        map["作业内容"] = ui->tableWidget->item(i, 0)->data(Qt::DisplayRole);
        map["基本时间"] = ui->tableWidget->item(i, 1)->data(Qt::DisplayRole);
        map["宽放率"] = ui->tableWidget->item(i, 2)->data(Qt::DisplayRole);
        map["标准时间"] = ui->tableWidget->item(i, 3)->data(Qt::DisplayRole);
        map["增值/非增值"] = ui->tableWidget->item(i, 4)->data(Qt::DisplayRole);
        map["操作分类"] = ui->tableWidget->item(i, 5)->data(Qt::DisplayRole);
        tableList << map;
    }

    QVariantMap totalMap;
    totalMap["table"] = tableList;
    totalMap["报表名称"] = ui->label_title->text();
    totalMap["所属产品名称"] = ui->label_product_name->text();
    totalMap["所属工艺名称"] = ui->label_product_name->text();
    totalMap["工站号"] = ui->label_product_name->text();
    totalMap["task-man"] = ui->label_product_name->text();
    totalMap["measure-date"] = ui->label_product_name->text();
    totalMap["measure-man"] = ui->label_product_name->text();
    totalMap["测量方法"] = ui->label_product_name->text();
    totalMap["数据单位"] = ui->label_product_name->text();

    return totalMap;
}

void ReportTableWidget::load(const QVariant &data)
{
    if(data.isNull())
    {
        return;
    }

    const auto list = data.toMap()["table"].toList();
    if(list.size() == 0)
    {
        return;
    }

    ui->tableWidget->clear();

    ui->tableWidget->setRowCount(list.size());
    ui->tableWidget->setColumnCount(6);
    QStringList headerList;
    headerList << "作业内容" << "基本时间" << "宽放率" << "标准时间" << "增值/非增值" << "操作分类";
    ui->tableWidget->setHorizontalHeaderLabels(headerList);
    for(int i = 0; i < list.size(); i++)
    {
        for(int j = 0; j < 6; j++)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem);
            ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    for(int i = 0; i < list.size(); i++)
    {
        const auto jobContent = list.at(i).toMap()["作业内容"];
        const auto basicTime = list.at(i).toMap()["基本时间"];
        const auto rate = list.at(i).toMap()["宽放率"];
        const auto stdTime = list.at(i).toMap()["标准时间"];
        const auto valueAdded = list.at(i).toMap()["增值/非增值"];
        const auto type = list.at(i).toMap()["操作分类"];

        ui->tableWidget->item(i, 0)->setData(Qt::DisplayRole, jobContent);
        ui->tableWidget->item(i, 1)->setData(Qt::DisplayRole, basicTime);
        ui->tableWidget->item(i, 2)->setData(Qt::DisplayRole, rate);
        ui->tableWidget->item(i, 3)->setData(Qt::DisplayRole, stdTime);
        ui->tableWidget->item(i, 4)->setData(Qt::DisplayRole, valueAdded);
        ui->tableWidget->item(i, 5)->setData(Qt::DisplayRole, type);
    }

    const auto reportHeader = data.toMap()["报表名称"].toString();
    const auto productName = data.toMap()["所属产品名称"].toString();
    const auto processName = data.toMap()["所属工艺名称"].toString();
    const auto workStationNum = data.toMap()["工站号"].toString();
    const auto taskMan = data.toMap()["task-man"].toString();
    const auto measureDate = data.toMap()["measure-date"].toString();
    const auto measureMan = data.toMap()["measure-man"].toString();
    const auto measureFunc = data.toMap()["测量方法"].toString();
    const auto dataUnit = data.toMap()["数据单位"].toString();

    ui->label_title->setText(reportHeader);
    ui->label_product_name->setText(productName);
    ui->label_process_name->setText(processName);
    ui->label_workStationNum->setText(workStationNum);
    ui->label_task_man->setText(taskMan);
    ui->label_measure_date->setText(measureDate);
    ui->label_measure_man->setText(measureMan);
    ui->label_measure_func->setText(measureFunc);
    ui->label_data_unit->setText(dataUnit);
}

void ReportTableWidget::setReportHeader(const QString &title)
{
    ui->label_title->setText(title);
}

QString ReportTableWidget::reportHeader() const
{
    return ui->label_title->text();
}
