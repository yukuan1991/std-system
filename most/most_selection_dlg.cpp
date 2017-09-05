#include "most_selection_dlg.h"
#include "ui_most_selection_dlg.h"
#include "utils/Qt-Utils/stl_extension.hpp"

most_selection_dlg::most_selection_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::most_selection_dlg)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader ()->setSectionResizeMode (QHeaderView::Stretch);
}

most_selection_dlg::~most_selection_dlg()
{
    delete ui;
}

QString most_selection_dlg::get_checked_item()
{
    for (int i = 0; i < ui->tableWidget->rowCount (); i++)
    {
        auto item = ui->tableWidget->item (i, 1);
        if (item->checkState () == Qt::Checked)
        {
            return item->text ();
        }
    }
    assert (false);
    return {};
}

void most_selection_dlg::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if (item->checkState () != Qt::Checked)
    {
        return;
    }

    ui->button_ok->setEnabled (true);

    auto row = item->row ();
    for (int i = 0; i < ui->tableWidget->rowCount (); i++)
    {
        if (i != row)
        {
            auto item = ui->tableWidget->item (i, 1);

            if (item->checkState () == Qt::Checked)
            {
                item->setCheckState (Qt::Unchecked);
            }
        }
    }
}
