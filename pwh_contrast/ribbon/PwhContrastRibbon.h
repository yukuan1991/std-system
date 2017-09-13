#ifndef PWHCONTRASTRIBBON_H
#define PWHCONTRASTRIBBON_H
#include "utils/ribbon.h"

class PwhContrastRibbon : public ribbon
{
    Q_OBJECT
signals:
    void importAnalysisFile();
//    void upChart();
//    void downChart();
    void exportPDF();
public:
    PwhContrastRibbon(QWidget* parent = nullptr);

    ribbon_tool* import_file_;
//    ribbon_tool* up_chart_;
//    ribbon_tool* down_chart_;
    ribbon_tool* export_pdf_;
private:
    void init();
};

#endif // PWHCONTRASTRIBBON_H
