#include "AddtoStdDatabaseDlg.h"
#include "ui_addtostddatabasedlg.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>

#include <QDebug>

AddtoStdDatabaseDlg::AddtoStdDatabaseDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddtoStdDatabaseDlg)
{
    ui->setupUi(this);

    connect(ui->buttonConfirm, &QPushButton::clicked, this, &AddtoStdDatabaseDlg::onButtonConfirmClicked);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &AddtoStdDatabaseDlg::reject);
    connect(ui->checkBox, &QCheckBox::stateChanged, this, &AddtoStdDatabaseDlg::onCheckAllStateChanged);


//    QStringList list;
//    list << "one" << "two" << "three";

//    ui->listWidget->addItems(list);

//    for(int i = 0; i < list.size(); i++)
//    {
//        ui->listWidget->item(i)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
//        ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
//    }

//    QVariantList varlist;
//    list << "名称" << "类型";
//    ui->treeWidget->setTreeHeader (varlist);
//    QFile file ("test.json");
//    file.open (QFile::ReadOnly);
//    const auto arr = file.readAll ();
//    ui->treeWidget->setTreeData (QJsonDocument::fromJson (arr).toVariant ());

}

AddtoStdDatabaseDlg::~AddtoStdDatabaseDlg()
{
    delete ui;
}

void AddtoStdDatabaseDlg::load(const QVariant &data)
{
   if(data.isNull())
   {
       return;
   }

   const auto directory = data.toMap()["目录结构"];
   ui->treeWidget->setTreeData(directory);

   const auto formMap = data.toMap()["form"].toMap();
   const auto list = formMap["作业内容"].toList();
   for(int i = 0; i < list.size(); i++)
   {
       ui->listWidget->addItem(list.at(i).toString());
   }

   for(int i = 0; i < list.size(); i++)
   {
       ui->listWidget->item(i)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
       ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
   }
}

QVariant AddtoStdDatabaseDlg::dump() const
{
    QVariantList checkedList;
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        auto state = ui->listWidget->item(i)->checkState();
        auto content = ui->listWidget->item(i)->data(Qt::DisplayRole).toString();
        QVariantMap map;
        map["选中状态"] = state;
        map["作业内容"] = content;
        checkedList << map;
    }

    QVariantMap map;
    map["form"] = checkedList;

    const auto selectedItems = ui->treeWidget->selectedItems();
    auto selectedItem = selectedItems.at(0);
    const auto selectedText = selectedItem->text(0);

    QStringList list;
    list << selectedText;
    auto parentItem = selectedItem->parent();
    while(parentItem)
    {
        list.prepend(parentItem->text(0));
        parentItem = parentItem->parent();
    }
    map["目录结构"] = list;


    return map;
}

void AddtoStdDatabaseDlg::onCheckAllStateChanged(int state)
{
    qDebug() << state;
    if(state == Qt::Checked)
    {
        for(int i = 0; i < ui->listWidget->count(); i++)
        {
            ui->listWidget->item(i)->setCheckState(Qt::Checked);
        }
    }
    else if(state == Qt::Unchecked)
    {
        for(int i = 0; i < ui->listWidget->count(); i++)
        {
            ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
        }
    }

}

void AddtoStdDatabaseDlg::onButtonConfirmClicked()
{
    const auto selectedItems = ui->treeWidget->selectedItems();
    if(selectedItems.size() == 0)
    {
        QMessageBox::information(this, "提示", "请选中一个目录位置！");
        return;
    }

    auto selectedItem = selectedItems.at(0);
    const auto selectedText = selectedItem->text(0);
    const auto selectedType = selectedItem->text(1);
    if(!selectedType.isEmpty())
    {
        QMessageBox::information(this, "提示", "添加位置有误，请重新选择！");
        return;
    }

    int checkedNum = 0;
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        auto state = ui->listWidget->item(i)->checkState();
        if(state == Qt::Checked)
        {
            checkedNum++;
        }
    }

    if(checkedNum == 0)
    {
        QMessageBox::information(this, "提示", "没有数据被选中!");
        return;
    }

    accept();
}


