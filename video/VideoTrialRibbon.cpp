#include "VideoTrialRibbon.h"
#include <base/lang/move.hpp>

VideoTrialRibbon::VideoTrialRibbon(QWidget *parent)
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
        b.set_title("更改操作");

        edit[1] = ::move (b);

        add_tab(edit, "编辑");
    }

    {
        std::array<ui_group, 2> edit;

        button_cell b;
        b.add ("导入", QPixmap ("png/导入.png"), import_);
        b.set_title("第一类");

        edit[0] = ::move (b);

        b.add ("无效时间", QPixmap ("png/无效时间.png"), inactive_time_);
        b.set_title("第二类");
        edit[1] = ::move (b);
        add_tab(edit, "视频");
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
        b.add ("Excel文档", QPixmap ("png/导出.png"), export_);
        b.set_title("导出");

        help[0] = ::move(b);

        add_tab(help, "报表");
    }

    connect(this, &VideoTrialRibbon::set_enabled, cut_, &ribbon_tool::setEnabled);
    connect(this, &VideoTrialRibbon::set_enabled, copy_, &ribbon_tool::setEnabled);
    connect(this, &VideoTrialRibbon::set_enabled, paste_, &ribbon_tool::setEnabled);
    connect(this, &VideoTrialRibbon::set_enabled, del_, &ribbon_tool::setEnabled);

    connect(this, &VideoTrialRibbon::set_enabled, add_row_, &ribbon_tool::setEnabled);

    connect(this, &VideoTrialRibbon::set_enabled, import_, &ribbon_tool::setEnabled);
    connect(this, &VideoTrialRibbon::set_enabled, inactive_time_, &ribbon_tool::setEnabled);

    connect(this, &VideoTrialRibbon::set_enabled, measure_date_, &ribbon_tool::setEnabled);
    connect(this, &VideoTrialRibbon::set_enabled, measure_man_, &ribbon_tool::setEnabled);
    connect(this, &VideoTrialRibbon::set_enabled, task_man_, &ribbon_tool::setEnabled);

    connect(this, &VideoTrialRibbon::set_enabled, export_, &ribbon_tool::setEnabled);

    connect(cut_, &ribbon_tool::clicked, this, &VideoTrialRibbon::cut);
    connect(copy_, &ribbon_tool::clicked, this, &VideoTrialRibbon::copy);
    connect(paste_, &ribbon_tool::clicked, this, &VideoTrialRibbon::paste);
    connect(del_, &ribbon_tool::clicked, this, &VideoTrialRibbon::del);

    connect(add_row_, &ribbon_tool::clicked, this, &VideoTrialRibbon::change_task_count);

    connect(import_, &ribbon_tool::clicked, this, &VideoTrialRibbon::import_data);
    connect(inactive_time_, &ribbon_tool::clicked, this, &VideoTrialRibbon::invalid_timespan);//////

    connect(measure_date_, &ribbon_tool::clicked, this, &VideoTrialRibbon::measure_date);
    connect(measure_man_, &ribbon_tool::clicked, this, &VideoTrialRibbon::measure_man);
    connect(task_man_, &ribbon_tool::clicked, this, &VideoTrialRibbon::task_man);

    connect(export_, &ribbon_tool::clicked, this, &VideoTrialRibbon::export_data);/////
}
