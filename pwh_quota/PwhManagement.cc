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
    QFile file ("test.json");
    file.open (QFile::ReadOnly);
    const auto arr = file.readAll ();
    ui->treeWidget->setTreeData (QJsonDocument::fromJson (arr).toVariant ());
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

    AddtoStdDatabaseDlg dlg;

    dlg.load(reportData);
    if(QDialog::Accepted == dlg.exec())
    {
        qDebug() << dlg.dump();
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
        map["path"] = addData.toMap()["path"];

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

