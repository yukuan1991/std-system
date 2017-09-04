#ifndef PTS_MODEL_H
#define PTS_MODEL_H

#include "utils/json_model.h"
#include <type_traits>
#include <memory>
#include <QVariant>
#include <string>
#include "mtm/arithmetic_resource.hpp"
#include <map>


class pts_model : public json_model
{
    Q_OBJECT
public:
    static std::unique_ptr<pts_model> make (PTS attr, QObject* parent = nullptr);
    ~pts_model () override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData (const QModelIndex& index, const QVariant& value, int role) override;
    void resize (unsigned size) override;
    void set_rate (double rate) { rate_ = rate;}

protected:
    pts_model (QObject* parent);
    bool init (PTS attr);
private:
    QVariant get_task_name (const QModelIndex& index, int role) const;
    bool set_task_name (const QModelIndex& index, const QVariant& value, int role);
    QVariant get_code (const QModelIndex& index, int role) const;
    bool set_code (const QModelIndex& index, const QVariant& value, int role);
    QVariant get_tmu (const QModelIndex& index, int role) const;
    QVariant get_base_time (const QModelIndex& index, int role) const;
    QVariant get_if_valuable (const QModelIndex& index, int role) const;
    QVariant get_allowance (const QModelIndex& index, int role) const;
    QVariant get_std (const QModelIndex& index, int role) const;

    void init_row (unsigned row);
private:
    using header_data_getter = QVariant (pts_model::*) (const QModelIndex&, int) const;
    using header_data_setter = bool (pts_model::*) (const QModelIndex&, const QVariant&, int);
    std::map<std::string, int> kv_tmu_;
    struct data_map
    {
        const char* header_;
        header_data_getter getter_;
    }
    data_map_ [6] =
    {
        {"代码", &pts_model::get_code},
        {"TMU", &pts_model::get_tmu},
        {"基本时间", &pts_model::get_base_time},
        {"增值/非增值", &pts_model::get_if_valuable},
        {"宽放率", &pts_model::get_allowance},
        {"标准工时", &pts_model::get_std}
    };

    struct set_data_map
    {
        const char* header_;
        header_data_setter setter_;
    }
    set_data_map_ [2]
    {
        {"代码", &pts_model::set_code}
    };
    double rate_ = 0;
};

#endif // PTS_MODEL_H
