#include "SaveTreeDialog.h"
#include "ui_SaveTreeDialog.h"
#include <QMessageBox>

SaveTreeDialog::SaveTreeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveTreeDialog)
{
    ui->setupUi(this);

    QVariantList list;
    list << "名称" << "类型";
    ui->treeWidget->setTreeHeader (list);

    connect(ui->buttonConfirm, &QPushButton::clicked, this, &SaveTreeDialog::onButtonConfirmClicked);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &SaveTreeDialog::reject);
}

SaveTreeDialog::~SaveTreeDialog()
{
    delete ui;
}

void SaveTreeDialog::load(const QVariant &data)
{
    ui->treeWidget->setTreeData(data);
}

QStringList SaveTreeDialog::dump() const
{
    const auto selectedList = ui->treeWidget->selectedItems();

    const auto selectedItem = selectedList.at(0);

    QStringList dirList;
    dirList << selectedItem->text(0);

    auto parentItem = selectedItem->parent();
    while(parentItem)
    {
        dirList.prepend(parentItem->text(0));
        parentItem = parentItem->parent();
    }

    return dirList;
}

void SaveTreeDialog::onButtonConfirmClicked()
{
    const auto selectedList = ui->treeWidget->selectedItems();
    if(selectedList.size() <= 0)
    {
        QMessageBox::information(nullptr, "提示", "请选择一个目录!");
        return;
    }

    const auto selectedItem = selectedList.at(0);
    const auto text = selectedItem->text(1);

    if(!text.isEmpty())
    {
        QMessageBox::information(nullptr, "提示", "选择位置有误！");
        return;
    }

    accept();
}
