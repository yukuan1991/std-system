﻿#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include "utils/json.hpp"
#include "utils/Qt-Utils/stl_extension.hpp"

using json = nlohmann::json;
constexpr int paste_role = Qt::UserRole + 100;

class json_model : public QAbstractTableModel
{
    Q_OBJECT
public:

    explicit json_model(QObject *parent = 0);
    json_model (const json_model&) = delete;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    std::string::size_type size() { return data_.size(); }
    virtual void resize (unsigned);

    optional<QString> get_header (const QModelIndex& index) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant decoration_data (const QModelIndex& index) const ;

    bool setData (const QModelIndex& index, const QVariant& value, int role = Qt::DisplayRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void add_editable (const QStringList& list);
    void remove_editable (const QStringList& list);
    json get_json () const;
    void load_json (const std::string& json_str);
    void load_json (const json& json_obj);
    int get_col_from_name (const QString& name) const;
    QVariant get_value_by_key (int row, const QString& key, int role = Qt::DisplayRole) const;
    void clear ();


protected:
    virtual bool paste_data (const QModelIndex& index, const QVariant& value);
    std::vector<std::map<QString, QVariant>> data_;
    QStringList headers_;
    QStringList edit_col_;
    QStringList paste_col_;
private:
    std::map<std::string, int> kv_tmu_;
};

#endif // TABLE_MODEL_H
