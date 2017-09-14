#include "StatView.h"
#include "ui_StatView.h"
#include <assert.h>

StatView::StatView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatView)
{
    ui->setupUi(this);
    connect (ui->pie, &PieView::hoveredItem, this, &StatView::onPieHovered);
    connect (ui->closeButton, &QPushButton::clicked, this, &StatView::closeView);
    initTable ();
}

StatView::~StatView()
{
    delete ui;
}

not_null<PieView *> StatView::pie() const
{
    return ui->pie;
}

bool StatView::load (const QVariantMap &data)
{
    QStringList types;
    types << "加工" << "搬运" << "检查" << "等待";

    QVariantList varList;
    auto sum = qreal {0};
    for (auto & it : types)
    {
        QVariantMap map;
        auto time = data[it].toDouble ();
        map ["percent"] = time;
        map ["name"] = it;

        varList << map;
        sum += time;

        auto item = cell ("时间", it); assert (item);
        item->setText (QString::number (time));
    }

    for (auto & it : types)
    {
        auto time = data[it].toDouble ();
        auto item = cell ("占比", it); assert (item);
        item->setText (QString::number (time / sum * 100) + " %");
    }

    cell ("时间", "增值")->setText (QString::number (data["加工"].toDouble ()));
    cell ("占比", "增值")->setText (QString::number (data["加工"].toDouble () / sum * 100) + " %");

    cell ("时间", "非增值")->setText (QString::number (sum - data["加工"].toDouble ()));
    cell ("占比", "非增值")->setText (QString::number ((sum - data["加工"].toDouble ()) / sum * 100) + " %");

    ui->pie->setSlices (varList);

    return true;
}

QVariant StatView::dump() const
{
    return {};
}

void StatView::setFileTitle(const QString &title)
{
    ui->file_title->setText(title);
}

void StatView::initTable()
{
    for (int i = 0; i < ui->dataTable->rowCount (); i ++)
    {
        for (int j = 0; j < ui->dataTable->columnCount (); j ++)
        {
            ui->dataTable->setItem (i, j, new QTableWidgetItem ());
        }
    }
}

void StatView::onPieHovered(const QString &name)
{
    for (int i = 0; i < ui->dataTable->rowCount (); i ++)
    {
        for (int j = 0; j < ui->dataTable->columnCount (); j ++)
        {
            if (ui->dataTable->verticalHeaderItem (i)->text () == name)
            {
                ui->dataTable->item (i, j)->setBackground (QColor (0xEE, 0xEE, 0xEE));
            }
            else
            {
                ui->dataTable->item (i, j)->setBackground (Qt::white);
            }
        }
    }
}

QTableWidgetItem *StatView::cell(const QString &horizontalHeader, const QString &verticalHeader) const
{
    auto row = int (-1);
    for (int i = 0; i < ui->dataTable->rowCount (); i ++)
    {
        const auto text = ui->dataTable->verticalHeaderItem (i)->text ();
        if (text == verticalHeader)
        {
            row = i;
        }
    }

    auto col = int (-1);
    for (int i = 0; i < ui->dataTable->columnCount (); i ++)
    {
        if (ui->dataTable->horizontalHeaderItem (i)->text () == horizontalHeader)
        {
            col = i;
        }
    }

    if (row == -1 or col == -1)
    {
        return null;
    }

    return ui->dataTable->item (row,col);
}
