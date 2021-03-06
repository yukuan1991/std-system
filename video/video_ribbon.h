﻿#pragma once
#include "utils/ribbon.h"

class video_ribbon : public ribbon
{
    Q_OBJECT
signals:
    void cut ();
    void copy ();
    void del ();
    void paste ();

    void change_task_count ();
    void change_example_cycle ();

    void import_data ();
    void invalid_timespan ();

    void measure_date ();
    void measure_man ();
    void task_man ();

    void export_data ();
public:
    video_ribbon(QWidget * parent = nullptr);
private:
    ribbon_tool *cut_, *copy_, *paste_, *del_;
    ribbon_tool *add_row_, *add_example_;
    ribbon_tool *export_;
    ribbon_tool *import_, *inactive_time_;
    ribbon_tool *measure_date_, *measure_man_, *task_man_;
};


