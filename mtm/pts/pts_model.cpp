#include "pts_model.h"
#include <QColor>
#include <QBrush>

using std::unique_ptr;

bool pts_model::init(PTS attr)
{
    switch (attr)
    {
    case PTS::left:
        headers_ << "作业内容" << "代码" << "数量*频次" << "TMU" << "评比系数" << "基本时间";
        edit_col_ << "作业内容" << "代码" << "数量*频次" << "评比系数";
        paste_col_ << "作业内容" << "代码" << "数量*频次" << "评比系数";
        break;
    case PTS::right:
        headers_ << "基本时间" << "评比系数" << "TMU" << "数量*频次" << "代码" << "作业内容";
        edit_col_ << "作业内容" << "代码" << "数量*频次" << "评比系数";
        paste_col_ << "作业内容" << "代码" << "数量*频次" << "评比系数";
        break;
    case PTS::result:
        headers_ << "作业内容" << "代码" << "数量*频次" << "TMU" << "评比系数" << "基本时间" << "宽放率" << "标准工时" << "增值/非增值" << "操作分类";
        edit_col_ << "作业内容" << "代码" << "数量*频次" << "评比系数" << "宽放率" << "操作分类";
        paste_col_ << "作业内容" << "代码" << "数量*频次" << "评比系数" << "宽放率" << "操作分类";
        break;
    default:
        assert (false);
    }
    std::tie (kv_tmu_, std::ignore) = read_tmu_data ();
    return true;
}

QVariant pts_model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::UserRole + 20)
    {
        return json_model::data (index, Qt::DisplayRole);
    }

    auto op_header = get_header (index);
    assert (op_header);
    if (role != Qt::BackgroundColorRole)
    {
        for (auto& it : this->data_map_)
        {
            if (*op_header == it.header_)
            {
                auto func_ptr = it.getter_;
                return (this->*func_ptr) (index, role);
            }
        }
    }
    return json_model::data (index, role);
}

bool pts_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid () and value.type () == QVariant::Double and role == Qt::UserRole + 100)
    {
        rate_ = value.toDouble ();
        return true;
    }

    auto op_header = get_header (index);
    assert (op_header);

    for (auto& it : this->set_data_map_)
    {

        if (*op_header == it.header_)
        {

            auto func_ptr = it.setter_;
            return (this->*func_ptr) (index, value, role);
        }
    }

    return json_model::setData (index, value, role);
}

bool pts_model::set_code(const QModelIndex &index, const QVariant &value, int role)
{
    assert (abs (rate_ >= 0.0001));

    if (role ==Qt::EditRole and value.isValid ())
    {
        if (QVariant::String == value.type ())
        {
            json_model::setData (index, value, role);
            return true;
        }
        else if (QVariant::StringList == value.type ())
        {
            json_model::setData (index, value, role);
        }
        if (QVariant::ByteArray == value.type () or QVariant::Int == value.type ())
        {
            auto var = json_model::data (index, Qt::DisplayRole);
            if (value.type () == QVariant::ByteArray)
            {
                auto byte = value.toByteArray ();
                std::string button_str = byte.data ();
                auto found = kv_tmu_.find (button_str);
                qDebug () << button_str.data ();
                assert (found != kv_tmu_.end ());

                if (!var.isValid () or var.type () == QVariant::String)
                {
                    QStringList list;
                    list << byte.data ();
                    setData (index, list, Qt::EditRole);
                }
                else if (var.type () == QVariant::StringList)
                {
                    auto list = var.toStringList ();
                    list << byte.data ();
                    setData (index, list, Qt::EditRole);
                }
            }
            else if (QVariant::Int == value.type ())
            {
                if (value.toInt () == 1 and var.type () == QVariant::StringList)
                {
                    auto list = var.toStringList ();
                    if (not list.empty())
                    {
                        list.removeLast ();
                    }
                    json_model::setData (index, list, Qt::EditRole);
                }
                else
                {
                    setData (index, QString{}, Qt::EditRole);
                }
            }
        }
    }
    else if(role == paste_role)
    {
        json_model::setData (index, value, role);
    }
    return false;
}

QVariant pts_model::get_tmu(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return {};
    }

    auto value = get_header_data (this, "代码", index, Qt::UserRole + 20);
    if (value.type () == QVariant::StringList)
    {
        auto list = value.toStringList ();
        int tmu = 0;
        for (auto& it : list)
        {
            auto found = kv_tmu_.find (it.toStdString ());
            assert (found != kv_tmu_.end ());
            tmu += found->second;
        }
        return tmu * get_header_data (this, "数量*频次", index).toInt ();
    }
    else
    {
        return {};
    }

}


QVariant pts_model::get_base_time(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return {};
    }

    auto tmu = get_header_data (this, "TMU", index);
    auto judge_rate = get_header_data (this, "评比系数", index);
    if (!tmu.isValid () or !judge_rate.isValid ())
    {
        return {};
    }
    return tmu.toInt () * rate_ * judge_rate.toDouble ();
}

QVariant pts_model::get_if_valuable(const QModelIndex &index, int role) const
{
    if (Qt::DisplayRole == role)
    {
        if (get_header_data (this, "操作分类", index).toString () == "加工")
        {
            return "增值";
        }
        else
        {
            return "非增值";
        }
    }
    return {};
}

QVariant pts_model::get_allowance(const QModelIndex &index, int role) const
{
    if (Qt::DisplayRole == role)
    {
        return QString::number (json_model::data (index, role).toDouble () * 100) + " %";
    }
    return {};
}

QVariant pts_model::get_std(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return (1 + get_header_data (this, "宽放率", index, Qt::UserRole + 20).toDouble ()) *
                get_header_data (this, "基本时间", index).toDouble ();
    }
    return {};
}


void pts_model::init_row(unsigned row)
{
    assert (row < rowCount ());
    auto col = get_header_col (this, "数量*频次");
    if (col > 0)
    {
        auto number_index = this->index (row, col);
        setData (number_index, 1, Qt::EditRole);
    }
    col = get_header_col (this, "评比系数");
    if (col > 0)
    {
        auto judge_rate_index = this->index (row, col);
        setData (judge_rate_index, double {1.0}, Qt::EditRole);
    }
    col = get_header_col (this, "操作分类");
    if (col > 0)
    {
        auto judge_rate_index = this->index (row, col);
        setData (judge_rate_index, "加工", Qt::EditRole);
    }
    col = get_header_col (this, "宽放率");
    if (col > 0)
    {
        auto judge_rate_index = this->index (row, col);
        setData (judge_rate_index, double {0}, Qt::EditRole);
    }
}

void pts_model::resize(unsigned size)
{
    json_model::resize (size);
    for (int i = 0; i < rowCount (); i ++)
    {
        init_row (i);
    }
}

QVariant pts_model::get_task_name(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    Q_UNUSED(role);
    return {};
}

bool pts_model::set_task_name(const QModelIndex &index, const QVariant &value, int role)
{
    return json_model::setData (index, value.toString (), role);
}

QVariant pts_model::get_code(const QModelIndex &index, int role) const
{
    auto code = json_model::data (index, Qt::DisplayRole);
    if (role == Qt::DisplayRole)
    {
        if (code.type () == QVariant::String)
        {
            return code;
        }
        else if (code.type () == QVariant::StringList)
        {
            auto code_list = code.toStringList ();
            QString code_data;

            for (auto& it : code_list)
            {
                auto split_list = it.split ('_'); assert (split_list.size () > 1);
                code_data += split_list[1];
                code_data += ".";
            }
            code_data.truncate (code_data.length () - 1);
            return code_data;
        }
    }

    if (role == Qt::ForegroundRole)
    {
        if (code.type () == QVariant::StringList)
        {
            return {};
        }
        else
        {
            return QBrush (QColor ("red"));
        }
    }

    return {};
}

pts_model::pts_model(QObject *parent) : json_model (parent)
{

}

std::unique_ptr<pts_model> pts_model::make(PTS attr, QObject *parent)
{
    std::unique_ptr<pts_model> obj {new pts_model {parent}};

    if (obj == nullptr or obj->init (attr) == false)
    {
        return nullptr;
    }

    return obj;
}

pts_model::~pts_model()
{

}
