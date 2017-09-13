#include "PwhManagement.h"
#include "ui_pwhmanagement.h"
#include <boost/filesystem.hpp>
//#include <Qt-Utils/qt.hpp>
//#include <Qt-Utils/krys_application.hpp>
#include <boost/scope_exit.hpp>
//#include "data_veryfication.h"
//#include "arithmetic_resource.hpp"
//#include "interface_control/modify_product_dlg.h"
#include <QMessageBox>
#include <QJsonDocument>
#include "ModifyProductDlg.h"
#include "AddtoStdDatabaseDlg.h"
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QInputDialog>

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
PwhManagement::PwhManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PwhManagement)
{
    ui->setupUi(this);

    QVariantList list;
    list << "名称" << "类型";
    ui->treeWidget->setTreeHeader (list);



}

PwhManagement::~PwhManagement()
{
    delete ui;
}

void PwhManagement::on_button_detail_clicked()
{
    const auto data = ui->treeWidget->currentSelectedData();

}

void PwhManagement::on_button_modify_clicked()
{
    QVariantMap map;
    map["工站号"] = "001";
    map["作业员"] = "sponge";
    map["测量日期"] = "2017-09-11";
    map["测量人"] = "krys";
    map["数据单位"] = "小时";

    ModifyProductDlg dlg;

    dlg.load(map);

    if(QDialog::Accepted == dlg.exec())
    {
        auto data = dlg.dump();
        qDebug() << QJsonDocument::fromVariant(data);
    }
}

void PwhManagement::on_button_addStdDatabase_clicked()
{
    const auto reportData = ui->reportWidget->dump();

    if(reportData.isNull())
    {
        QMessageBox::information(this, "提示", "请先选中目录下的一个文件！");
        return;
    }

    AddtoStdDatabaseDlg dlg;
    dlg.initTreeData(io->pullData("standard"));
    dlg.load(reportData);
    if(QDialog::Accepted == dlg.exec())
    {
        const auto addData = dlg.dump();
        const auto numData = addData.toMap()["table"].toList();

        const auto tableData = reportData.toMap()["table"].toList();

        QVariantMap map;
        QVariantList list;
        for(int i = 0; i < numData.size(); i++)
        {
            const auto num = numData.at(i).toInt();
            list << tableData.at(num);
        }
        map["table"] = list;

        const auto items = ui->treeWidget->selectedItems();
        const auto item = items.at(0);
        const auto name = item->text(0);

        const auto standardPath = addData.toMap()["path"].toStringList();

        const auto type = reportData.toMap()["测量方法"].toString();

        io->addNode (standardPath, name, "standard", "mod", map);
    }
}

void PwhManagement::on_button_exportDF_clicked()
{
    const auto saveFileName = QFileDialog::getSaveFileName(nullptr, "生成PDF", "PwhContrast File", "*.pdf");
    if(saveFileName.isEmpty())
    {
        return;
    }

    QPrinter printerPixmap(QPrinter::HighResolution);
    printerPixmap.setPageSize(QPrinter::A4);  //设置纸张大小为A4
    printerPixmap.setOutputFormat(QPrinter::PdfFormat);  //设置输出格式为pdf
    printerPixmap.setOutputFileName(saveFileName);   //设置输出路径
    QPixmap pixmap = ui->reportWidget->grab();

    QPainter painterPixmap;
    painterPixmap.begin(&printerPixmap);
    QRect rect = painterPixmap.viewport();
    int multiple = rect.width()/pixmap.width();
    painterPixmap.scale(multiple, multiple); //将图像(所有要画的东西)在pdf上放大multiple-1倍
    painterPixmap.drawPixmap(0, 0, pixmap);  //画图
    painterPixmap.end();
}

void PwhManagement::on_button_reportHeader_clicked()
{
    const auto oldTitle = ui->reportWidget->reportHeader();
    QInputDialog dlg;
    dlg.setWindowTitle("表头设置");
    dlg.setLabelText("请输入表头数据:");
    dlg.setTextValue(oldTitle);


    if(QDialog::Accepted == dlg.exec())
    {
        if(dlg.textValue().isEmpty())
        {
            QMessageBox::information(this, "提示", "报表名称为空！");
            return;
        }

        ui->reportWidget->setReportHeader(dlg.textValue());
    }
}

void PwhManagement::initTreeWidget(const QVariant& data)
{
    ui->treeWidget->setTreeData(data);
}

void PwhManagement::onTreeWidgetClicked()
{
    const auto treeData = ui->treeWidget->currentSelectedData();
    const auto content = treeData.toMap()["content"];
    const auto data = QJsonDocument::fromJson(content).toVariant();


}

