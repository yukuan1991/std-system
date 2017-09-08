#include "JsonTree.h"
#include <QStringList>
#include<QTreeWidgetItem>
#include <base/lang/range.hpp>
#include <boost/range/counting_range.hpp>
#include <QMessageBox>
#include <QInputDialog>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>
#include <assert.h>

#include <QDebug>

using std::make_unique;
using namespace boost;
using namespace boost::adaptors;

JsonTree::JsonTree(QWidget *parent)
    :QTreeWidget (parent)
{
    connect (this, &JsonTree::treeDataChanged, this, &JsonTree::resetTree);
    connect (this, &JsonTree::treeHeaderChanged, this, &JsonTree::resetHeader);

    setSelectionMode(QAbstractItemView::SingleSelection);
}

QVariant JsonTree::currentSelectedData() const
{
    const auto selectedItems = this->selectedItems();
    if(selectedItems.size() == 0)
    {
        return {};
    }

    assert (selectedItems.size () == 1);

    const auto selected = selectedItems.at (0);

    QStringList list;

    for (auto item = selected; item != null; item = item->parent ())
    {
        list.prepend (item->text (0));
    }


    auto topList = treeData ().toList ();

    while (1)
    {
        QVariant var;
        for (auto & it : topList)
        {
            if (it.toMap ()["name"] == list.at (0))
            {
                var = it;
                break;
            }
        }

        if (var.isNull ())
        {
            return {};
        }

        if (list.size () == 1)
        {
            return var;
        }

        list.pop_front ();

        auto newTop = var.toMap ()["content"];

        if (newTop.type () != QVariant::List)
        {
            return {};
        }

        topList = newTop.toList ();
    }

    return {};
}

void JsonTree::resetHeader()
{
    QStringList header;
    treeHeader ().toList ()
            | execute ([&] (auto && c) { header << c.toString (); });

    setColumnCount (header.size ());
    setHeaderItem (new QTreeWidgetItem (header));

    resetTree ();
}

void JsonTree::resetTree()
{
    const auto data = treeData ();
    for (auto & it : data.toList ())
    {
        auto top = setupItem (it);
        if (top)
        {
            addTopLevelItem (top.release ());
        }
    }
}

JsonTree::~JsonTree()
{

}

std::unique_ptr<QTreeWidgetItem> JsonTree::setupItem (const QVariant &data)
{
    if (data.type () != QVariant::Map)
    {
        return null;
    }

    auto map = data.toMap ();
    auto ret = make_unique<QTreeWidgetItem> ();

    const auto header = headerItem ();
    counting_range (0, header->columnCount ())
            | transformed ([&] (auto && c) { return header->text (c); })
            | indexed (int {0})
            | execute ([&] (auto && c) { ret->setText (static_cast<int> (c.index ()), map [c.value ()].toString ()); });

    if (map["name"].toString ().trimmed ().isEmpty ())
    {
        return null;
    }

    ret->setText (0, map ["name"].toString ());

    const auto content = map ["content"];

    for (auto & child : content.toList ())
    {
        auto childItem = setupItem (child);
        if (childItem == null)
        {
            continue;
        }

        ret->addChild (childItem.release ());
    }

    return ret;
}
