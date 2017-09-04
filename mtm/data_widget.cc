#include "data_widget.h"
#include "ui_data_widget.h"
#include "view/table_view.h"
#include <QScrollBar>
#include <QMessageBox>
#include <QDebug>

data_widget::data_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::data_widget)
{
    ui->setupUi(this);
    ui->table_result->setItemDelegate(result_delegate_.get());
    view_ = ui->table_result;
    set_view();

    connect(result_model_.get(), &pts_model::dataChanged,
            [this] { auto sum = get_std_time_sum(); emit std_time_sum(sum); });
}

data_widget::~data_widget()
{
    delete ui;
}

QString data_widget::get_std_time_sum() const
{
    auto col = 5;
    double sum = 0;
    for (int row = 0; row < static_cast<int>(result_model_->size ()); ++row)
    {
        auto pos = result_model_->index (row, col);
        auto vat = result_model_->data (pos);
        if (vat.isNull ())
        {
            continue;
        }
        else
        {
            auto time = vat.toDouble ();
            sum += time;
        }
    }
    return QString::number(sum, 'f', 2);
}

void data_widget::add_code(const QVariant &code)
{
    if (result_model_->size() <= 0)
    {
        QMessageBox::information (this, "代码", "请新建一个表格");
        return;
    }

    if (view_ == nullptr or view_->selectionModel()->selectedIndexes ().empty ())
    {
        QMessageBox::information (this, "代码", "请选中一个表格");
        return;
    }

    assert (view_);

    auto list = view_->selectionModel ()->selectedIndexes ();
    decltype (list) code_list;

    for (auto& index : list)
    {
        auto variant = index.model ()->headerData (index.column (), Qt::Horizontal, Qt::DisplayRole);
        QString header = variant.toString ();
        if (header == "代码")
        {
            code_list.append (index);
        }
    }

    if (code_list.empty ())
    {
        QMessageBox::information (this, "代码", "请选中代码这一列");
        return;
    }

    auto min_row = 99999;
    auto min_row_index = -1;
    for (int i = 0; i < code_list.size (); i++)
    {
        if (code_list[i].row () < min_row)
        {
            min_row_index = i;
            min_row = code_list[i].row ();
        }
    }
    assert (min_row_index != -1 and min_row_index < code_list.size ());

    view_->model ()->setData (code_list[min_row_index], code);

}

void data_widget::set_unit(double unit)
{
    this->result_model_->setData (QModelIndex (), unit, Qt::UserRole + 100);
}

void data_widget::next_code()
{
    if (view_ == nullptr or view_->model () == nullptr)
    {
        return;
    }

    auto list_index = view_->selectionModel ()->selectedIndexes ();


    QModelIndex code_index;
    for (auto& it : list_index)
    {
        auto variant = it.model ()->headerData (it.column (), Qt::Horizontal, Qt::DisplayRole);
        QString header = variant.toString ();
        if (header == "代码")
        {
            code_index = it;
            break;
        }
    }


    if (!code_index.isValid () or code_index.row () >= code_index.model ()->rowCount () - 1)
    {
        return;
    }

    auto next_index = view_->model ()->index (code_index.row () + 1, code_index.column ());
    view_->scrollTo(next_index);
    assert (next_index.isValid ());

    view_->clearSelection ();
    view_->selectionModel ()->select (next_index, QItemSelectionModel::Select);
}

json data_widget::save_result() try
{
    json result = json::array();
    QVariant vat;
    auto model = result_model_.get ();
    for(int j=0; j < model->rowCount();++j)
    {
        json json_row_obj = json::object ();

        auto key = "作业内容"s;
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toString ().toStdString ();

        key = "代码";
        auto& code_arr = json_row_obj[key];
        code_arr = json::array ();
        vat = get_header_data (model, key.data (), j, Qt::UserRole + 20);
        auto list = vat.toStringList ();
        for (auto & it : list)
        {
            code_arr.push_back (it.toStdString ());
        }

        key = "数量*频次";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toInt ();

        key = "TMU";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toInt ();

        key = "评比系数";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        key = "基本时间";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        key = "宽放率";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toString ().toStdString ();

        key = "标准工时";
        vat = get_header_data (model, key.data (), j);
        json_row_obj["标准时间"] = vat.toDouble ();

        key = "增值/非增值";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toString ().toStdString ();

        key = "操作分类";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toString ().toStdString ();

        result.push_back (std::move (json_row_obj));
    }

    return result;
}
catch (std::exception &e)
{
    qDebug () << __LINE__ << e.what();
    return {};
}

void data_widget::set_row(int num)
{
    emit line_exists (num != 0);

    result_model_->resize (static_cast<unsigned int>(num));
    ui->table_result->setModel(nullptr);
    ui->table_result->setModel(result_model_.get ());
}

bool data_widget::load_result(const json &result) try
{
    QModelIndex index;
    result_model_->resize(result.size());
    assert(static_cast<int>(result.size()) == result_model_->rowCount());

    for(uint32_t i=0; i<result.size(); ++i)
    {
        const auto& row  = result[i];
        std::string key = "作业内容";
        std::string task_name = row[key];

        auto col = get_header_col (result_model_.get (), key.data ());
        index = result_model_->index(i,col);
        result_model_->setData(index, task_name.data (), Qt::EditRole);

        key = "代码";
        const auto& code = row[key];
        QStringList list;
        for(unsigned j = 0; j < code.size(); ++j)
        {
            std::string str = code[j];
            list << str.data ();
        }
        col = get_header_col (result_model_.get (), key.data ());
        index = result_model_->index(i,col);
        result_model_->setData(index,list, Qt::EditRole);

        key = "数量*频次";
        int amount = row[key];
        index = get_header_index (result_model_.get (), key.data (), i);
        result_model_->setData(index, amount, Qt::EditRole);

        key = "评比系数";
        double rate = row["评比系数"];
        index = result_model_->index(i,4);
        result_model_->setData(get_header_index (result_model_.get (), key.data (), i), rate, Qt::EditRole);

        key = "宽放率";
        std::string allowance = row [key];
        auto pos = allowance.find('%',0); assert (pos != std::string::npos);
        allowance.erase(pos,1);

        result_model_->setData(get_header_index (result_model_.get (), key.data (), i),
                               QString{allowance.data ()}.toDouble () / 100, Qt::EditRole);

        key = "操作分类";
        std::string operation_type = row [key];
        result_model_->setData(get_header_index (result_model_.get (), key.data (), i), operation_type.data (), Qt::EditRole);
    }
    return true;

}
catch (std::exception &e)
{
    qDebug () << __LINE__ << e.what();
    return false;
}

bool data_widget::task_content_check()
{
    for (int i = 0; i < result_model_->rowCount (); i ++)
    {
        if (get_header_data (result_model_.get (), "作业内容", i).toString ().trimmed ().isEmpty ())
        {
            QMessageBox::information (this, "作业内容", "作业内容的第" + QString::number (i + 1) + "行为空");
            return false;
        }
        if (get_header_data (result_model_.get (), "代码", i, Qt::UserRole + 20).type () != QVariant::StringList)
        {
            QMessageBox::information (this, "作业内容", "作业内容的第" + QString::number (i + 1) + "行的代码不符合格式或为空");
            return false;
        }
    }

    return true;
}

void data_widget::clear()
{
    result_model_->clear ();
    ui->table_result->setModel (nullptr);
    ui->table_result->setModel (result_model_.get ());
}

void data_widget::on_cut()
{
    if (view_ != nullptr)
    {
        view_->on_copy_del (table_view::OPERATION_COPY | table_view::OPERATION_DEL);
    }
}

void data_widget::on_copy()
{
    if (view_ != nullptr)
    {
        view_->on_copy_del (table_view::OPERATION_COPY);
    }
}

void data_widget::on_paste()
{
    if (view_ != nullptr)
    {
        view_->on_paste ();
    }
}

void data_widget::on_del()
{
    if (view_ != nullptr)
    {
        view_->on_copy_del (table_view::OPERATION_DEL);
    }
}

void data_widget::set_view()
{
    view_->horizontalHeader ()->setSectionResizeMode (QHeaderView::Interactive);
    view_->verticalHeader ()->setSectionResizeMode (QHeaderView::Fixed);

    auto scroll = make_unique<QScrollBar> ();
    view_->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOn);
    connect (scroll.get (), &QScrollBar::valueChanged, [=] (int value)
    {
            view_->verticalScrollBar ()->setValue (value);
    });

    view_->setVerticalScrollBar (scroll.release ());
}
