#include "ProductFamilyWidget.h"
#include "ui_productfamilywidget.h"
#include <QJsonDocument>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QJsonArray>
#include <QMenu>
#include <QDebug>
#include <QJsonObject>
#include "utils/json.hpp"


ProductFamilyWidget::ProductFamilyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductFamilyWidget)
{
    ui->setupUi(this);

    QVariantList list;
    ui->treeWidget->setTreeHeader (list);

    initConn();
    ui->treeWidget->installEventFilter(this);
    connect (this, &ProductFamilyWidget::add, this, &ProductFamilyWidget::onAdd);
}

ProductFamilyWidget::~ProductFamilyWidget()
{
    delete ui;
}

bool ProductFamilyWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->treeWidget)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* w = static_cast<QMouseEvent*>(event);
            if(w->button() == Qt::RightButton)
            {
                QMenu menu;
                auto add = menu.addAction("增加");
                auto remove = menu.addAction("删除");
                auto modify = menu.addAction("修改");
                connect(add, &QAction::triggered, this, &ProductFamilyWidget::onAddButtonClicked);
                connect(remove, &QAction::triggered, this, &ProductFamilyWidget::onRemoveButtonClicked);
                connect(modify, &QAction::triggered, this, &ProductFamilyWidget::onModifyButtonClicked);
                menu.exec(QCursor::pos());
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return QWidget::eventFilter(watched, event);
    }
}

void ProductFamilyWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent (event);
    if (io != null)
    {
        auto var = io->pullData ("product");
        ui->treeWidget->setTreeData (var);
    }
}

void ProductFamilyWidget::initConn()
{
    connect(ui->addButton, &QPushButton::clicked, this, &ProductFamilyWidget::onAddButtonClicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &ProductFamilyWidget::onRemoveButtonClicked);
    connect(ui->modifyButton, &QPushButton::clicked, this, &ProductFamilyWidget::onModifyButtonClicked);
}

void ProductFamilyWidget::onAddButtonClicked ()
{
    const auto selectedItems = ui->treeWidget->selectedItems();

    const auto name = QInputDialog::getText (this, "添加项目", "请输入项目名称");
    QStringList list;

    if(selectedItems.size() == 0)
    {
        emit add (list, name);
        return;
    }

    auto selectedItem = selectedItems.at(0);
    const auto selectedText = selectedItem->text(0);
    const auto selectedType = selectedItem->text(1);

    if(not selectedType.isEmpty())
    {
        QMessageBox::information (this, "提示", "添加位置有误，请重新选择！");
        return;
    }

    if(name.isEmpty())
    {
        QMessageBox::information(this, "提示", "目录名不能为空!");
        return;
    }

    list << selectedText;

    auto parentItem = selectedItem->parent();
    while(parentItem)
    {
        list.prepend(parentItem->text(0));
        parentItem = parentItem->parent();
    }

    emit add (list, name);
}

void ProductFamilyWidget::onRemoveButtonClicked()
{
    const auto selectedItems = ui->treeWidget->selectedItems();
    if(selectedItems.size() == 0)
    {
        QMessageBox::information(this, "提示", "请选中一个目录位置！");
        return;
    }

    auto selectedItem = selectedItems.at(0);
    const auto selectedText = selectedItem->text(0);
    auto ret = QMessageBox::question(this, "提示", "确认删除?");
    if(ret == QMessageBox::No)
    {
        return;
    }

    QStringList list;
    list << selectedText;
    auto parentItem = selectedItem->parent();
    while(parentItem)
    {
        list.prepend(parentItem->text(0));
        parentItem = parentItem->parent();
    }

    emit ui->treeWidget->remove(list);
}

void ProductFamilyWidget::onModifyButtonClicked()
{
    const auto selectedItems = ui->treeWidget->selectedItems();
    if(selectedItems.size() == 0)
    {
        QMessageBox::information(this, "提示", "请选中一个目录位置！");
        return;
    }

    auto selectedItem = selectedItems.at(0);
    const auto selectedText = selectedItem->text(0);

    const auto name = QInputDialog::getText(this, "修改项目", "请输入新名称");
    if(name.isEmpty())
    {
        QMessageBox::information(this, "提示", "目录名不能为空!");
        return;
    }

    QStringList previousList;
    QStringList modifyList;
    previousList << selectedText;
    modifyList << name;
    auto parentItem = selectedItem->parent();
    while(parentItem)
    {
        previousList.prepend(parentItem->text(0));
        modifyList.prepend(parentItem->text(0));
        parentItem = parentItem->parent();
    }

    emit ui->treeWidget->modify(previousList, modifyList);
}

void ProductFamilyWidget::onAdd (const QStringList &list, const QString &name)
{
    auto var = ui->treeWidget->treeData ();
    auto tmp = list;
    auto newVar = refreshVariant (tmp, name, var);

    io->pushData ("product", newVar);
    ui->treeWidget->setTreeData (io->pullData ("product"));
}


QVariant ProductFamilyWidget::refreshVariant(QStringList & list, const QString &name, const QVariant var)
{
    QJsonObject obj;
    obj["name"] = name;
    obj["content"] = QJsonArray ();

    auto totalData = QJsonDocument::fromVariant (var).array ();

    if (totalData.isEmpty ())
    {
        totalData.append (obj);
    }

    return totalData.toVariantList ();
}

