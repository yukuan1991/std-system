#include "mod_data_widget.h"
#include "ui_mod_data_widget.h"
#include <QMessageBox>
#include <QScrollBar>

mod_data_widget::mod_data_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_data_widget)
{
    ui->setupUi(this);
    ui->table_left->setItemDelegate (left_delegate_.get ());
    ui->table_right->setItemDelegate (right_delegate_.get ());
    ui->table_result->setItemDelegate (result_delegate_.get ());

    views_.push_back (ui->table_result);
    views_.push_back (ui->table_left);
    views_.push_back (ui->table_right);
    set_views();

    connect(result_model_.get(), &pts_model::dataChanged,
            [this] { auto sum = get_std_time_sum(); emit std_time_sum(sum); });
}

mod_data_widget::~mod_data_widget()
{
    delete ui;
}

QString mod_data_widget::get_std_time_sum() const
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

void mod_data_widget::add_code(const QVariant &code)
{
    if (current_view_ == nullptr or current_view_->selectionModel ()->selectedIndexes ().empty ())
    {
        QMessageBox::information (this, "代码", "请选中一个表格");
        return;
    }

    assert (current_view_);
    auto list = current_view_->selectionModel ()->selectedIndexes ();
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

    current_view_->model ()->setData (code_list[min_row_index], code);
}

void mod_data_widget::set_unit(double unit)
{
    this->left_model_->setData (QModelIndex (), unit, Qt::UserRole + 100);
    this->right_model_->setData (QModelIndex (), unit, Qt::UserRole + 100);
    this->result_model_->setData (QModelIndex (), unit, Qt::UserRole + 100);
}

void mod_data_widget::next_code()
{
    if (current_view_ == nullptr or current_view_->model () == nullptr)
    {
        return;
    }

    auto list_index = current_view_->selectionModel ()->selectedIndexes ();


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

    auto next_index = current_view_->model ()->index (code_index.row () + 1, code_index.column ());
    current_view_->scrollTo(next_index);
    assert (next_index.isValid ());

    current_view_->clearSelection ();
    current_view_->selectionModel ()->select (next_index, QItemSelectionModel::Select);
}

json mod_data_widget::save_left() try
{
    json left = json::array();
    QVariant vat;
    auto model = left_model_.get ();
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

        key = "MOD";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toInt ();

        key = "评比系数";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        key = "基本时间";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        left.push_back (std::move (json_row_obj));
    }
    return left;
}
catch (std::exception &e)
{
    qDebug () << __LINE__ << e.what();
    return {};
}

void mod_data_widget::set_row(int num)
{
    emit line_exists (num != 0);

    left_model_->resize (static_cast<unsigned int>(num));
    ui->table_left->setModel(nullptr);
    ui->table_left->setModel(left_model_.get ());

    right_model_->resize (static_cast<unsigned int>(num));
    ui->table_right->setModel(nullptr);
    ui->table_right->setModel(right_model_.get ());
    result_model_->resize (static_cast<unsigned int>(num));
    ui->table_result->setModel(nullptr);
    ui->table_result->setModel(result_model_.get ());
}

bool mod_data_widget::task_content_check()
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

void mod_data_widget::clear()
{
    result_model_->clear ();
    ui->table_result->setModel (nullptr);
    ui->table_result->setModel (result_model_.get ());
    left_model_->clear ();
    ui->table_left->setModel (nullptr);
    ui->table_left->setModel (left_model_.get ());
    right_model_->clear ();
    ui->table_right->setModel (nullptr);
    ui->table_right->setModel (right_model_.get ());
}

void mod_data_widget::on_cut()
{
    if (current_view_ != nullptr)
    {
        current_view_->on_copy_del (table_view::OPERATION_COPY | table_view::OPERATION_DEL);
    }
}

void mod_data_widget::on_copy()
{
    if (current_view_ != nullptr)
    {
        current_view_->on_copy_del (table_view::OPERATION_COPY);
    }
}

void mod_data_widget::on_paste()
{
    if (current_view_ != nullptr)
    {
        current_view_->on_paste ();
    }
}

void mod_data_widget::on_del()
{
    if (current_view_ != nullptr)
    {
        current_view_->on_copy_del (table_view::OPERATION_DEL);
    }
}

json mod_data_widget::json_data()
{
    auto left = save_left (); assert (left.is_array());
    auto right = save_right (); assert (right.is_array());
    auto result = save_result (); assert (result.is_array());

    json total_data = {{"左手",std::move(left)}
                       ,{"右手",std::move(right)}
                       ,{"总计",std::move(result)}};
    return total_data;
}

json mod_data_widget::save_result() try
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

        key = "MOD";
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

void mod_data_widget::on_view_clicked()
{
    QObject* src = sender (); assert (src);
    current_view_ = dynamic_cast<table_view*>(src); assert (current_view_);

    for (typename decltype (views_)::size_type i = 0; i < views_.size (); i ++)
    {
        if (views_[i] != current_view_)
        {
            views_[i]->clearSelection ();
        }
    }
}

void mod_data_widget::set_views()
{
    for (auto iter : views_)
    {
        assert (iter);
        connect (iter, &table_view::mouse_pressed, this, &mod_data_widget::on_view_clicked);
        iter->horizontalHeader ()->setSectionResizeMode (QHeaderView::Interactive);
        iter->verticalHeader ()->setSectionResizeMode (QHeaderView::Fixed);

        auto scroll = make_unique<QScrollBar> ();
        iter->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOn);
        connect (scroll.get (), &QScrollBar::valueChanged, [=] (int value)
        {
            for (auto inner_iter : views_)
            {
                inner_iter->verticalScrollBar ()->setValue (value);
            }
        });

        iter->setVerticalScrollBar (scroll.release ());
    }
}

json mod_data_widget::save_right() try
{
    json right = json::array();
    QVariant vat;
    auto model = right_model_.get ();
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

        key = "MOD";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toInt ();

        key = "评比系数";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        key = "基本时间";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        right.push_back (std::move (json_row_obj));
    }

    return right;
}
catch (std::exception &e)
{
    qDebug () << __LINE__ << e.what();
    return {};
}

bool mod_data_widget::load_left(const json &left) try
{
    QModelIndex index;
    left_model_->resize(left.size());
    assert(static_cast<int>(left.size()) == left_model_->rowCount());

    for(uint32_t i=0; i<left.size(); ++i)
    {
        const auto& row  = left[i];
        std::string key = "作业内容";
        std::string task_name = row[key];

        auto col = get_header_col (left_model_.get (), key.data ());
        index = left_model_->index(i,col);
        left_model_->setData(index, task_name.data (), Qt::EditRole);

        key = "代码";
        const auto& code = row[key];
        QStringList list;
        for(unsigned j = 0; j < code.size(); ++j)
        {
            std::string str = code[j];
            list << str.data ();
        }
        col = get_header_col (left_model_.get (), key.data ());
        index = left_model_->index(i,col);
        left_model_->setData(index,list, Qt::EditRole);

        key = "数量*频次";
        int amount = row[key];
        index = get_header_index (left_model_.get (), key.data (), i);
        left_model_->setData(index, amount, Qt::EditRole);

        key = "评比系数";
        double rate = row["评比系数"];
        index = left_model_->index(i,4);
        left_model_->setData(get_header_index (left_model_.get (), key.data (), i), rate, Qt::EditRole);
    }

    return true;
}
catch (std::exception &e)
{
    qDebug () << __LINE__ << e.what();
    return false;
}


bool mod_data_widget::load_right(const json &right) try
{
    QModelIndex index;
    right_model_->resize(right.size());
    assert(static_cast<int>(right.size()) == right_model_->rowCount());

    for(uint32_t i=0; i<right.size(); ++i)
    {
        const auto& row  = right[i];
        std::string key = "作业内容";
        std::string task_name = row[key];

        auto col = get_header_col (right_model_.get (), key.data ());
        index = right_model_->index(i,col);
        right_model_->setData(index, task_name.data (), Qt::EditRole);

        key = "代码";
        const auto& code = row[key];
        QStringList list;
        for(unsigned j = 0; j < code.size(); ++j)
        {
            std::string str = code[j];
            list << str.data ();
        }
        col = get_header_col (right_model_.get (), key.data ());
        index = right_model_->index(i,col);
        right_model_->setData(index,list, Qt::EditRole);

        key = "数量*频次";
        int amount = row[key];
        index = get_header_index (right_model_.get (), key.data (), i);
        right_model_->setData(index, amount, Qt::EditRole);

        key = "评比系数";
        double rate = row["评比系数"];
        index = right_model_->index(i,4);
        right_model_->setData(get_header_index (right_model_.get (), key.data (), i), rate, Qt::EditRole);
    }
    return true;
}
catch (std::exception &e)
{
    qDebug () << __LINE__ << e.what();
    return false;
}


bool mod_data_widget::load_result(const json &result) try
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


