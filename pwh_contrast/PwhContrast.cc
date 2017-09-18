#include "PwhContrast.h"
#include "ui_pwhcontrast.h"
#include <assert.h>
#include <memory>
#include "pwh_contrast/production_management_button_tree_dlg.h"
#include "utils/arithmetic_resource.hpp"
#include <QMessageBox>
#include "utils/data_veryfication.h"
#include "utils/Qt-Utils/json.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <base/io/file/file.hpp>
#include <base/utils/charset.hpp>
#include <QFileDialog>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <QPalette>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

using ptr_func = std::vector<taskInfo>(*)(std::string_view);
QMap<QString, ptr_func> map
{
    {"vmaf" , readVaf},
    {"vtaf", readVaf},
    {"modaf", readPts},
    {"mostaf", readPts},
    {"mtmaf", readPts}
};

PwhContrast::PwhContrast(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PwhContrast)
{
    ui->setupUi(this);
    setup_more_ui();

    setWindowTitle("产品工时对比");
    QVariantList list;
    list << "名称" << "类型";
    ui->tree_product->setTreeHeader (list);
}

PwhContrast::~PwhContrast()
{
    delete ui;
}

void PwhContrast::initTreeData(const QVariant &data)
{
    ui->tree_product->setTreeData(data);
}

void PwhContrast::load()
{
    const auto selectedList = ui->tree_product->selectedItems();
    if(selectedList.size() <= 0)
    {
        QMessageBox::information(this, "提示", "请选中目录中的一个文件!");
        return;
    }

    const auto item = selectedList.at(0);
    const auto fileName = item->text(0);
    const auto func = item->text(1);
    if(func.isEmpty())
    {
        QMessageBox::information(this, "提示", "请选中目录下的一个文件！");
        return;
    }

    const auto fileData = ui->tree_product->currentSelectedData();
    qDebug() << QJsonDocument::fromVariant(fileData).toJson().toStdString().data();
    const auto type = fileData.toMap()["类型"].toString();

    const auto text = QJsonDocument::fromVariant(fileData.toMap()["content"]).toJson().toStdString();

    std::vector<taskInfo> taskinfo;
    if(type == "视频分析法(量产)")
    {
        taskinfo = (map["vmaf"])(text);
    }
    else if(type == "视频分析法(试产)")
    {
        taskinfo = (map["vtaf"])(text);
    }
    else if(type == "mod")
    {
        taskinfo = (map["modaf"])(text);
    }
    else if(type == "most")
    {
        taskinfo = (map["mostaf"])(text);
    }
    else if(type == "mtm")
    {
        taskinfo = (map["mtmaf"])(text);
    }

    if(!parseAnalysisFile(fileName, taskinfo))
    {
        QMessageBox::information(this, "添加文件", "添加文件失败，文件已损坏！");
    }
}

void PwhContrast::upChart()
{
    ui->listWidget->up();
}

void PwhContrast::downChart()
{
    ui->listWidget->down();
}

void PwhContrast::exportPDF()
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
    QPixmap pixmap = ui->listWidget->grab();

    QPainter painterPixmap;
    painterPixmap.begin(&printerPixmap);
    QRect rect = painterPixmap.viewport();
    int multiple = rect.width()/pixmap.width();
    painterPixmap.scale(multiple, multiple); //将图像(所有要画的东西)在pdf上放大multiple-1倍
    painterPixmap.drawPixmap(0, 0, pixmap);  //画图
    painterPixmap.end();
}



bool PwhContrast::parseAnalysisFile(const QString& fileName, const std::vector<taskInfo> &data)
{
    QJsonDocument document;
    QJsonObject json;
    qreal processing_time = 0;
    qreal checking_time = 0;
    qreal moving_time = 0;
    qreal waiting_time = 0;
    for(auto & it : data)
    {
        if(it.type == workType::Processing)
        {
            processing_time += it.stdTime;
        }
        else if(it.type == workType::Checking)
        {
            checking_time += it.stdTime;
        }
        else if(it.type == workType::Moving)
        {
            moving_time += it.stdTime;
        }
        else if(it.type == workType::Waiting)
        {
            waiting_time += it.stdTime;
        }
    }
    json.insert("加工", processing_time);
    json.insert("检查", checking_time);
    json.insert("搬运", moving_time);
    json.insert("等待", waiting_time);

    document.setObject(json);
    const auto content = document.toVariant();
    ui->listWidget->append(fileName, content);

    return true;
}


void PwhContrast::setup_more_ui()
{
    for (int i = 0; i < ui->listWidget->count (); i++)
    {
        auto item = ui->listWidget->item (i); assert(item);
        auto size = item->sizeHint ();

        size.setHeight (30);
        item->setSizeHint (size);
        item->setTextAlignment(Qt::AlignCenter);
    }
}


