#include "ExamineApproveMain.h"
#include "ui_ExamineApproveMain.h"
#include <QTableWidget>
#include <QMessageBox>

#include <QDebug>
#include <QFile>
#include <QJsonDocument>

ExamineApproveMain::ExamineApproveMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamineApproveMain)
{
    ui->setupUi(this);

    setWindowTitle("审批");

    ui->examineApproveTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->examineApproveTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->examineApproveTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->infoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->infoTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->infoTable->setSelectionMode(QAbstractItemView::SingleSelection);

    QFile file("approval/test.json");
    file.open(QIODevice::ReadOnly);
    auto data = file.readAll();
    auto document = QJsonDocument::fromJson(data);

    auto var = document.toVariant();
    loadExamineApproveTable(var);

    file.close();

    QFile info("approval/2.vaf");
    info.open(QIODevice::ReadOnly);
    auto infoData = info.readAll();
    auto infoDocument = QJsonDocument::fromJson(infoData);
    auto infoVar = infoDocument.toVariant();
    loadRelatedInfoTable(infoVar);
    info.close();

    connect(ui->examineApproveTable, &QTableWidget::cellClicked, this, &ExamineApproveMain::onCellClicked);
    connect(ui->buttton_agree, &QPushButton::clicked, this, &ExamineApproveMain::onButtonAgreeClicked);
    connect(ui->button_disagree, &QPushButton::clicked, this, &ExamineApproveMain::onButtonDisagreeClicked);
}

ExamineApproveMain::~ExamineApproveMain()
{
    delete ui;
}

void ExamineApproveMain::loadExamineApproveTable(const QVariant &data)
{
    const auto list = data.toList();
    const auto rows = list.size();
    qDebug() << rows;
    if(rows <= 0)
    {
        return;
    }
    QStringList headerList;
    headerList << "ID" << "申请人" << "内容" << "状态" << "申请时间";
    const auto cols = headerList.size();
    ui->examineApproveTable->setRowCount(rows);
    ui->examineApproveTable->setColumnCount(cols);
    ui->examineApproveTable->setHorizontalHeaderLabels(headerList);

    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            ui->examineApproveTable->setItem(row, col, new QTableWidgetItem);
            ui->examineApproveTable->item(row, col)->setTextAlignment(Qt::AlignCenter);
        }
    }

    const auto idCol = findHeaderCol(headerList, "ID");
    const auto personCol = findHeaderCol(headerList, "申请人");
    const auto contentCol = findHeaderCol(headerList, "内容");
    const auto statusCol = findHeaderCol(headerList, "状态");
    const auto dateCol = findHeaderCol(headerList, "申请时间");

    for(int row = 0; row < rows; row++)
    {
        const auto id = list.at(row).toMap()["ID"];
        const auto person = list.at(row).toMap()["申请人"];
        const auto content = list.at(row).toMap()["内容"];
        const auto status = list.at(row).toMap()["状态"];
        const auto date = list.at(row).toMap()["申请时间"];

        setTableData(ui->examineApproveTable, row, idCol, id);
        setTableData(ui->examineApproveTable, row, personCol, person);
        setTableData(ui->examineApproveTable, row, contentCol, content);
        setTableData(ui->examineApproveTable, row, statusCol, status);
        setTableData(ui->examineApproveTable, row, dateCol, date);
    }
}

void ExamineApproveMain::loadRelatedInfoTable(const QVariant &data)
{
    const auto list = data.toList();
    const auto rows = list.size();
    if(rows <= 0)
    {
        return;
    }
    QStringList headerList;
    headerList << "所属产品名称" <<  "所属工艺名称"  << "工站号" << "作业内容" << "基本时间" << "宽放率" << "标准时间" << "增值/非增值"
               << "操作分类" << "测量方法" << "作业员" << "测量人" << "测量日期";
    const auto cols = headerList.size();
    ui->infoTable->setRowCount(rows);
    ui->infoTable->setColumnCount(cols);
    ui->infoTable->setHorizontalHeaderLabels(headerList);

    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            ui->infoTable->setItem(row, col, new QTableWidgetItem);
            ui->infoTable->item(row, col)->setTextAlignment(Qt::AlignCenter);
        }
    }

    const auto productNameCol = findHeaderCol(headerList, "所属产品名称");
    const auto processNameCol = findHeaderCol(headerList, "所属工艺名称");
    const auto workStationCol = findHeaderCol(headerList, "工站号");
    const auto jobContentCol = findHeaderCol(headerList, "作业内容");
    const auto basicTimeCol = findHeaderCol(headerList, "基本时间");
    const auto rateCol = findHeaderCol(headerList, "宽放率");
    const auto stdTimeCol = findHeaderCol(headerList, "标准时间");
    const auto valueAddedCol = findHeaderCol(headerList, "增值/非增值");
    const auto typeCol = findHeaderCol(headerList, "操作分类");
    const auto funcCol = findHeaderCol(headerList, "测量方法");
    const auto taskManCol = findHeaderCol(headerList, "作业员");
    const auto measureManCol = findHeaderCol(headerList, "测量人");
    const auto measureDateCol = findHeaderCol(headerList, "测量日期");

    for(int row = 0; row < rows; row++)
    {
        const auto productName = list.at(row).toMap()["所属产品名称"];
        setTableData(ui->infoTable, row, productNameCol, productName);
        const auto processName = list.at(row).toMap()["所属工艺名称"];
        setTableData(ui->infoTable, row, processNameCol, processName);
        const auto workStation = list.at(row).toMap()["工站号"];
        setTableData(ui->infoTable, row, workStationCol, workStation);
        const auto jobContent = list.at(row).toMap()["作业内容"];
        setTableData(ui->infoTable, row, jobContentCol, jobContent);
        const auto basicTime = list.at(row).toMap()["基本时间"];
        setTableData(ui->infoTable, row, basicTimeCol, basicTime);
        const auto rate = list.at(row).toMap()["宽放率"];
        setTableData(ui->infoTable, row, rateCol, rate);
        const auto stdTime = list.at(row).toMap()["标准时间"];
        setTableData(ui->infoTable, row, stdTimeCol, stdTime);
        const auto valueAdded = list.at(row).toMap()["增值/非增值"];
        setTableData(ui->infoTable, row, valueAddedCol, valueAdded);
        const auto type = list.at(row).toMap()["操作分类"];
        setTableData(ui->infoTable, row, typeCol, type);
        const auto func = list.at(row).toMap()["测量方法"];
        setTableData(ui->infoTable, row, funcCol, func);
        const auto taskMan = list.at(row).toMap()["作业员"];
        setTableData(ui->infoTable, row, taskManCol, taskMan);
        const auto measureMan = list.at(row).toMap()["测量人"];
        setTableData(ui->infoTable, row, measureManCol, measureMan);
        const auto measureDate = list.at(row).toMap()["测量日期"];
        setTableData(ui->infoTable, row, measureDateCol, measureDate);
    }
}

void ExamineApproveMain::onCellClicked(int row)
{
    QVariant id = ui->examineApproveTable->item(row, 0)->data(Qt::DisplayRole);

    qDebug() << id;
    emit selectedData(id);
}

void ExamineApproveMain::onButtonAgreeClicked()
{
    const auto list = ui->examineApproveTable->selectedItems();
    if(list.size() <= 0)
    {
        QMessageBox::information(this, "提示", "没有数据被选中！");
        return;
    }
    const auto item = list.at(0);
    const auto row = item->row();
    QVariant id = ui->examineApproveTable->item(row, 0)->data(Qt::DisplayRole);

    qDebug() << id;
    emit agree(id);
}

void ExamineApproveMain::onButtonDisagreeClicked()
{
    const auto list = ui->examineApproveTable->selectedItems();
    if(list.size() <= 0)
    {
        QMessageBox::information(this, "提示", "没有数据被选中！");
        return;
    }
    const auto item = list.at(0);
    const auto row = item->row();
    QVariant id = ui->examineApproveTable->item(row, 0)->data(Qt::DisplayRole);

    qDebug() << id;
    emit disagree(id);
}

int ExamineApproveMain::findHeaderCol(const QStringList &list, const QString &colName)
{
    int col = -1;
    if(list.size() <= 0 or colName.isEmpty())
    {
        return col;
    }
    const auto found = std::find(list.begin(), list.end(), colName);
    if(found != list.end())
    {
        col = found - list.begin();
    }
    return col;
}

void ExamineApproveMain::setTableData(QTableWidget *table, int row, int col, const QVariant &data)
{
    if(table == nullptr)
    {
        return;
    }
    if(col != -1 and !data.isNull())
    {
        table->item(row, col)->setData(Qt::DisplayRole, data);
    }

}
