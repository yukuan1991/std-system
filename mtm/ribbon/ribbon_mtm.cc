#include "ribbon_mtm.h"
#include <base/lang/move.hpp>


ribbon_mtm::ribbon_mtm(QWidget *parent)
    : ribbon(parent)
{
    {
        std::array<ui_group, 2> edit;

        button_cell b;
        b.add ("剪切", QPixmap ("png/剪切.png"), cut_);
        b.add ("复制", QPixmap ("png/复制.png"), copy_);
        b.add ("粘贴", QPixmap ("png/粘贴.png"), paste_);
        b.add ("删除", QPixmap ("png/删除.png"), del_);
        b.set_title("文档操作");

        edit[0] = ::move (b);

        b.add ("改变作业项数", QPixmap ("png/作业项数.png"), add_row_);
        b.set_title("行数变更");

        edit[1] = ::move (b);

        add_tab(edit, "编辑");
    }

    {
        std::array<ui_group, 1> setting;

        button_cell b;
        b.add ("测量日期", QPixmap ("png/测量日期.png"), measure_date_);
        b.add ("测量人", QPixmap ("png/测量人.png"), measure_man_);
        b.add ("作业员", QPixmap ("png/作业员.png"), task_man_);
        b.set_title("信息设置");

        setting[0] = ::move (b);

        add_tab(setting, "设置");
    }

    {
        std::array<ui_group, 1> help;

        button_cell b;
        b.add ("帮助", QPixmap ("png/帮助.png"), help_);
        b.set_title("联系我们");

        help[0] = ::move(b);

        add_tab(help, "帮助");
    }

    connect(this, &ribbon_mtm::set_enabled, cut_, &ribbon_tool::setEnabled);
    connect(this, &ribbon_mtm::set_enabled, copy_, &ribbon_tool::setEnabled);
    connect(this, &ribbon_mtm::set_enabled, paste_, &ribbon_tool::setEnabled);
    connect(this, &ribbon_mtm::set_enabled, del_, &ribbon_tool::setEnabled);
    connect(this, &ribbon_mtm::set_enabled, add_row_, &ribbon_tool::setEnabled);
    connect(this, &ribbon_mtm::set_enabled, measure_date_, &ribbon_tool::setEnabled);
    connect(this, &ribbon_mtm::set_enabled, measure_man_, &ribbon_tool::setEnabled);
    connect(this, &ribbon_mtm::set_enabled, task_man_, &ribbon_tool::setEnabled);


    connect(cut_, &ribbon_tool::clicked, this, &ribbon_mtm::cut);
    connect(copy_, &ribbon_tool::clicked, this, &ribbon_mtm::copy);
    connect(paste_, &ribbon_tool::clicked, this, &ribbon_mtm::paste);
    connect(del_, &ribbon_tool::clicked, this, &ribbon_mtm::del);
    connect(add_row_, &ribbon_tool::clicked, this, &ribbon_mtm::add_row);

    connect(measure_date_, &ribbon_tool::clicked, this, &ribbon_mtm::measure_date);
    connect(measure_man_, &ribbon_tool::clicked, this, &ribbon_mtm::measure_man);
    connect(task_man_, &ribbon_tool::clicked, this, &ribbon_mtm::task_man);

    connect(help_, &ribbon_tool::clicked, this, &ribbon_mtm::help);

}
