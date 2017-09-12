#include "PwhContrastRibbon.h"
#include <base/lang/move.hpp>

PwhContrastRibbon::PwhContrastRibbon(QWidget* parent)
    : ribbon(parent)
{
    {
        std::array<ui_group, 1> edit;

        button_cell b;

        b.add("导入", QPixmap("png/导入.png"), import_file_);
        b.add("上移", QPixmap("png/上移.png"), up_chart_);
        b.add("下移", QPixmap("png/下移.png"), down_chart_);
        b.add("生成PDF", QPixmap("png/导出.png"), export_pdf_);
        b.set_title("图表操作");

        edit[0] = ::move (b);

//        b.add("添加表一", QPixmap("png/添加对比1.png"), add_first_table);
//        b.add("添加表二", QPixmap("png/添加对比2.png"), add_second_table);
//        b.add("添加表三", QPixmap("png/添加对比3.png"), add_third_table);
//        b.set_title("添加对比");

//        edit[1] = ::move (b);

//        b.add("清除表一", QPixmap("png/清除表1.png"), clear_first_table);
//        b.add("清除表二", QPixmap("png/清除表2.png"), clear_second_table);
//        b.add("清除表三", QPixmap("png/清除表3.png"), clear_third_table);
//        b.set_title("清除数据");

//        edit[2] = ::move (b);

        add_tab(edit, "编辑");
    }

    init();
}

void PwhContrastRibbon::init()
{
    connect(import_file_, &ribbon_tool::clicked, this, &PwhContrastRibbon::importAnalysisFile);
    connect(up_chart_, &ribbon_tool::clicked, this, &PwhContrastRibbon::upChart);
    connect(down_chart_, &ribbon_tool::clicked, this, &PwhContrastRibbon::downChart);
    connect(export_pdf_, &ribbon_tool::clicked, this, &PwhContrastRibbon::exportPDF);


//    connect(add_first_table, &RibbonTool::clicked, this, &PwhContrastRibbon::add_first_table_clicked);
//    connect(add_second_table, &RibbonTool::clicked, this, &PwhContrastRibbon::add_second_table_clicked);
//    connect(add_third_table, &RibbonTool::clicked, this, &PwhContrastRibbon::add_third_table_clicked);
//    connect(clear_first_table, &RibbonTool::clicked, this, &PwhContrastRibbon::clear_first_table_clicked);
//    connect(clear_second_table, &RibbonTool::clicked, this, &PwhContrastRibbon::clear_second_table_clicked);
//    connect(clear_third_table, &RibbonTool::clicked, this, &PwhContrastRibbon::clear_third_table_clicked);

}
