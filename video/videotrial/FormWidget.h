﻿#pragma once
#include <QWidget>
#include "video/videotrial/VideoDelegate.h"
#include <QTableView>
#include "utils/view/table_view.h"
#include <memory>
#include <QTableWidgetItem>
#include <vector>
#include "video/video_form_split.h"
#include <memory>
#include <utils/json.hpp>
#include <QModelIndex>
#include <optional>
#include "utils/utils.hpp"
#include "video/videotrial/VideoFormModel.h"

using json = nlohmann::json;

namespace Ui {
class FormWidget;
}

class FormWidget final : public QWidget
{
    Q_OBJECT
public:
    static constexpr int max_row = 12;

public:
    explicit FormWidget(QWidget *parent = 0);
    ~FormWidget();
    void mark (long long time_val);
    int row ();
    void set_row (int num);
    void add_row (int num);
    void reduce_row (int num);
    bool task_content_check ();
    void scroll_to_index (const QModelIndex& index);

    void on_paste ();
    void on_copy ();
    void on_cut ();
    void on_del ();

    void loadTask(const QVariant& task);
    void loadData(const QVariant& data);
    void loadResult(const QVariant& result);


    std::optional<action_ratio> operation_ratio () const;
    std::optional<overall_stats> operation_stats () const;
    std::vector<qreal> cycle_times () const;
private:
    std::optional<QModelIndex> get_next_index (const QModelIndex&) const;

    void table_clicked (const QModelIndex&);

    QVariant taskData();
    QVariant observationTime();
    QVariant resultData();
    void set_scrolls ();

    void initConn();
    void initTable();
    void setTable();
public:
    json export_data ();
    QVariant dump();
    void clear ();

signals:
    void total_time_changed (const QString& sum);
    void data_changed ();

private:
    Ui::FormWidget *ui;
    const std::unique_ptr<VideoFormModel> src_model_ = std::make_unique<VideoFormModel> ();
    const std::unique_ptr<video_form_split> model_des_ = std::make_unique<video_form_split> ();
    const std::unique_ptr<video_form_split> model_data_ = std::make_unique<video_form_split> ();
    const std::unique_ptr<video_form_split> model_result_ = std::make_unique<video_form_split> ();
    const std::unique_ptr<VideoDelegate> des_delegate_ = std::make_unique<VideoDelegate> ();

    std::vector<QTableView*> views_;
    table_view* current_view_ = nullptr;
};
