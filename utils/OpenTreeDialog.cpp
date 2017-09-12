#include "OpenTreeDialog.h"
#include "ui_OpenTreeDialog.h"

OpenTreeDialog::OpenTreeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenTreeDialog)
{
    ui->setupUi(this);

    QVariantList list;
    list << "名称" << "类型";
    ui->treeWidget->setTreeHeader (list);

    connect(ui->buttonConfirm, &QPushButton::clicked, this, &OpenTreeDialog::accept);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &OpenTreeDialog::reject);
}

OpenTreeDialog::~OpenTreeDialog()
{
    delete ui;
}

void OpenTreeDialog::load(const QVariant &data)
{
    ui->treeWidget->setTreeData(data);
}

QVariant OpenTreeDialog::dump()
{
    return ui->treeWidget->currentSelectedData();
}

