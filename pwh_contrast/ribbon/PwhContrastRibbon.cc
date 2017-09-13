#include "PwhContrastRibbon.h"
#include <base/lang/move.hpp>

PwhContrastRibbon::PwhContrastRibbon(QWidget* parent)
    : ribbon(parent)
{
    {
        std::array<ui_group, 1> edit;

        button_cell b;

        b.add("导入", QPixmap("png/导入.png"), import_file_);
//        b.add("上移", QPixmap("png/上移.png"), up_chart_);
//        b.add("下移", QPixmap("png/下移.png"), down_chart_);
        b.add("生成PDF", QPixmap("png/导出.png"), export_pdf_);
        b.set_title("图表操作");

        edit[0] = ::move (b);

        add_tab(edit, "编辑");
    }

    init();
}

void PwhContrastRibbon::init()
{
    connect(import_file_, &ribbon_tool::clicked, this, &PwhContrastRibbon::importAnalysisFile);
//    connect(up_chart_, &ribbon_tool::clicked, this, &PwhContrastRibbon::upChart);
//    connect(down_chart_, &ribbon_tool::clicked, this, &PwhContrastRibbon::downChart);
    connect(export_pdf_, &ribbon_tool::clicked, this, &PwhContrastRibbon::exportPDF);
}
