#include "video_ribbon.h"
#include <base/lang/move.hpp>

video_ribbon::video_ribbon(QWidget * parent)
    :ribbon (parent)
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
        b.add ("更改样例循环", QPixmap ("png/测量日期.png"), add_example_);
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

    connect(this, &video_ribbon::set_enabled, cut_, &ribbon_tool::setEnabled);
    connect(this, &video_ribbon::set_enabled, copy_, &ribbon_tool::setEnabled);
    connect(this, &video_ribbon::set_enabled, paste_, &ribbon_tool::setEnabled);
    connect(this, &video_ribbon::set_enabled, del_, &ribbon_tool::setEnabled);

    connect(this, &video_ribbon::set_enabled, add_row_, &ribbon_tool::setEnabled);
    connect(this, &video_ribbon::set_enabled, add_example_, &ribbon_tool::setEnabled);

    connect(this, &video_ribbon::set_enabled, import_, &ribbon_tool::setEnabled);
    connect(this, &video_ribbon::set_enabled, inactive_time_, &ribbon_tool::setEnabled);

    connect(this, &video_ribbon::set_enabled, measure_date_, &ribbon_tool::setEnabled);
    connect(this, &video_ribbon::set_enabled, measure_man_, &ribbon_tool::setEnabled);
    connect(this, &video_ribbon::set_enabled, task_man_, &ribbon_tool::setEnabled);

    connect(this, &video_ribbon::set_enabled, export_, &ribbon_tool::setEnabled);

    connect(cut_, &ribbon_tool::clicked, this, &video_ribbon::cut);
    connect(copy_, &ribbon_tool::clicked, this, &video_ribbon::copy);
    connect(paste_, &ribbon_tool::clicked, this, &video_ribbon::paste);
    connect(del_, &ribbon_tool::clicked, this, &video_ribbon::del);

    connect(add_row_, &ribbon_tool::clicked, this, &video_ribbon::change_task_count);
    connect(add_example_, &ribbon_tool::clicked, this, &video_ribbon::change_example_cycle);//////

    connect(import_, &ribbon_tool::clicked, this, &video_ribbon::import_data);
    connect(inactive_time_, &ribbon_tool::clicked, this, &video_ribbon::invalid_timespan);//////

    connect(measure_date_, &ribbon_tool::clicked, this, &video_ribbon::measure_date);
    connect(measure_man_, &ribbon_tool::clicked, this, &video_ribbon::measure_man);
    connect(task_man_, &ribbon_tool::clicked, this, &video_ribbon::task_man);

    connect(export_, &ribbon_tool::clicked, this, &video_ribbon::export_data);/////
}
