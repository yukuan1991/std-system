﻿#pragma once
#include "utils/ribbon.h"

class ribbon_mod : public ribbon
{
    Q_OBJECT
signals:
    void cut();
    void copy();
    void paste();
    void del();
    void add_row();
    void measure_date();
    void measure_man();
    void task_man();
public:
    ribbon_mod(QWidget * parent = nullptr);
private:
    ribbon_tool *cut_, *copy_, *paste_, *del_;
    ribbon_tool *add_row_;
    ribbon_tool *measure_date_, *measure_man_, *task_man_;
};

