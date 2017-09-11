#include "PwhListWidget.h"
#include "pwh_contrast/StatView.h"
#include <memory>
#include <assert.h>
#include <QMessageBox>
#include <QDebug>

PwhListWidget::PwhListWidget(QWidget *parent)
    : QListWidget (parent)
{

}

void PwhListWidget::insert(const QVariant &data, int index)
{
    auto item = std::make_unique<QListWidgetItem> (this);
    auto chart = std::make_unique<StatView> (this);
    auto map = data.toMap();
    chart->load(map);

    item->setSizeHint(QSize(200, 200));

    connect(chart.get(), &StatView::closeView, this , &PwhListWidget::close);

    insertItem(index, item.get());

    setItemWidget(item.release(), chart.release());
}

void PwhListWidget::up()
{
    qDebug() << "up";
//    if(selectedItems().size() != 1)
//    {
//        QMessageBox::information(this, "提示", "当前没有选中图表对象！");
//        return;
//    }
//    auto current_row = currentRow();
//    if(current_row <= 0)
//    {
//        current_row = count();
//    }
//    setCurrentRow(current_row - 1);

    auto current = currentItem();
    auto current_row = currentRow();
    if(!current)
    {
        QMessageBox::information(this, "提示", "当前没有选中的图表对象!");
        return;
    }
    auto item = takeItem(current_row);
    if(current_row <= 0)
    {
        current_row = count();
    }

    insertItem(current_row - 1, item);
}

void PwhListWidget::down()
{
    qDebug() << "down";
    if(selectedItems().size() != 1)
    {
        QMessageBox::information(this, "提示", "当前没有选中图表对象！");
        return;
    }
    auto current_row = currentRow();
    if(current_row >= count() - 1)
    {
        current_row = -1;
    }
    setCurrentRow(current_row + 1);
}

void PwhListWidget::close()
{
    auto s = dynamic_cast<QWidget *> (sender());
    assert (s);

    for (int i = 0; i < count(); i ++)
    {
        auto theItem = item (i);
        if (theItem == null)
        {
            continue;
        }

        if (itemWidget(theItem) == s)
        {
            std::unique_ptr<QListWidgetItem> (takeItem(i));
        }
    }
}
