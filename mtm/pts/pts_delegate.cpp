#include "pts_delegate.h"
#include <QLineEdit>
#include <regex>
#include <assert.h>
#include <QPainter>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "mtm/arithmetic_resource.hpp"
#include <boost/algorithm/string.hpp>
#include <QStyleOptionViewItem>
#include "code_edit.h"


pts_delegate::pts_delegate(QObject *parent) : QStyledItemDelegate (parent)
{
    std::tie (kv_tmu_, std::ignore) = read_tmu_data ();
}

QWidget *pts_delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    auto header = index.model ()->headerData (index.column (), Qt::Horizontal, Qt::DisplayRole);
    auto str_header = header.toString ();
    if (str_header == "作业内容")
    {
        return new QLineEdit {parent};
    }
    else if (str_header == "代码")
    {
        return new QLineEdit {parent};
    }
    else if (str_header == "数量*频次")
    {
        return new QSpinBox {parent};
    }
    else if (str_header == "评比系数")
    {
        return new QDoubleSpinBox {parent};
    }
    else if (str_header == "操作分类")
    {
        return new QComboBox {parent};
    }
    else if (str_header == "宽放率")
    {
        return new QLineEdit {parent};
    }
    return nullptr;
}

void pts_delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto header = index.model ()->headerData (index.column (), Qt::Horizontal, Qt::DisplayRole);
    auto str_header = header.toString ();
    if (str_header == "作业内容")
    {
        auto edit = dynamic_cast<QLineEdit*> (editor); assert (edit);
        edit->setText (index.data (Qt::DisplayRole).toString ());
    }
    else if (str_header == "代码")
    {
        auto edit = dynamic_cast<QLineEdit*> (editor); assert (edit);
        edit->setText (index.data (Qt::DisplayRole).toString ());
    }
    else if (str_header == "数量*频次")
    {
        auto edit = dynamic_cast<QSpinBox*> (editor); assert (edit);
        edit->setMinimum (0);
        edit->setValue (index.data (Qt::DisplayRole).toInt ());
    }
    else if (str_header == "评比系数")
    {
        auto edit = dynamic_cast<QDoubleSpinBox*> (editor); assert (edit);
        edit->setMinimum (0.0);
        edit->setMaximum (10.0);
        edit->setSingleStep (0.1);
        edit->setValue (index.data (Qt::DisplayRole).toDouble ());
    }
    else if (str_header == "操作分类")
    {
        auto edit = dynamic_cast<QComboBox*> (editor); assert (edit);
        edit->addItem ("加工");
        edit->addItem ("搬运");
        edit->addItem ("检查");
        edit->addItem ("等待");
        edit->setCurrentText (index.data (Qt::DisplayRole).toString ());
    }
    else if (str_header == "宽放率")
    {
        auto edit = dynamic_cast<QLineEdit*> (editor); assert (edit);
        auto str = index.data ().toString ().toStdString ();
        auto pos = str.find_first_of (' '); assert (pos != std::string::npos);
        str.erase(pos);
        edit->setText (str.data ());
    }
}

void pts_delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto header = model->headerData (index.column (), Qt::Horizontal, Qt::DisplayRole);
    auto str_header = header.toString ();
    if (str_header == "作业内容")
    {
        auto edit = dynamic_cast<QLineEdit*> (editor); assert (edit);
        model->setData (index, edit->text (), Qt::EditRole);
    }
    else if (str_header == "代码")
    {
        set_code (editor, model, index);
    }
    else if (str_header == "数量*频次")
    {
        auto edit = dynamic_cast<QSpinBox*> (editor); assert (edit);
        model->setData (index, edit->value (), Qt::EditRole);
    }
    else if (str_header == "评比系数")
    {
        auto edit = dynamic_cast<QDoubleSpinBox*> (editor); assert (edit);
        model->setData (index, edit->value (), Qt::EditRole);
    }
    else if (str_header == "操作分类")
    {
        auto edit = dynamic_cast<QComboBox*> (editor); assert (edit);
        model->setData (index, edit->currentText (), Qt::EditRole);
    }
    else if (str_header == "宽放率")
    {
        auto edit = dynamic_cast<QLineEdit*>(editor); assert (edit);
        bool is_ok;
        auto val = edit->text().toDouble (&is_ok);
        if (is_ok)
        {
            model->setData (index, val / 100, Qt::EditRole);
            return;
        }
    }
}

void pts_delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry (option.rect);
}

//void pts_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    auto model = index.model (); assert (model);
//    auto header = model->headerData (index.column (), Qt::Horizontal).toString ();
//
//    if (header == "宽放率")
//    {
//        if (option.state & QStyle::State_Selected)
//        {
//            if (option.state & QStyle::State_Active)
//            {
//                painter->setPen (Qt::white);
//                painter->fillRect (option.rect, option.palette.highlight ());
//            }
//            else
//            {
//                painter->setPen (Qt::black);
//                painter->fillRect (option.rect, option.palette.window ());
//            }
//        }
//        else
//        {
//            painter->setPen (Qt::black);
//        }
//
//        painter->drawText (option.rect, "12345");
//        return;
//    }
//    QStyledItemDelegate::paint (painter, option, index);
//}


void pts_delegate::set_code(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto edit = dynamic_cast<QLineEdit*> (editor); assert (edit);
    std::string raw_code = edit->text ().toStdString ();
    boost::trim (raw_code);

    std::for_each (raw_code.begin (), raw_code.end (), [] (auto& ch) {if (ch >= 'a' and ch <= 'z') ch &= ~(32);});

    boost::regex splitter ("[[:alnum:]]+");
    boost::smatch hit;
    std::string::const_iterator start = raw_code.begin ();
    std::string::const_iterator stop = raw_code.end ();

    QStringList code_list;
    auto tmu = 0;
    while (boost::regex_search (start, stop, hit, splitter))
    {
        const auto code = hit[0].str ();

        const auto prefix_code = "mtm_" + code;

        auto found = kv_tmu_.find (prefix_code);
        if (found == kv_tmu_.end ())
        {
            model->setData (index, edit->text ().trimmed (), Qt::EditRole);
            return;
        }

        tmu += found->second;
        code_list << prefix_code.data ();
        start = hit[0].second;
    }

    if (code_list.empty ())
    {
        model->setData (index, QString{}, Qt::EditRole);
    }
    else
    {
        model->setData (index, code_list, Qt::EditRole);
    }
}
