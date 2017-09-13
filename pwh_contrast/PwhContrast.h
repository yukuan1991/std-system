#ifndef PWHCONTRAST_H
#define PWHCONTRAST_H

#include <QWidget>
#include <optional>
#include "utils/Qt-Utils/json.hpp"
#include "utils/Model/product_structure_model.h"
#include "utils/Qt-Utils/openaf.h"
#include "IoManipulator.h"

namespace Ui {
class PwhContrast;
}

class QTableWidget;
using nlohmann::json;

class PwhContrast : public QWidget
{
    Q_OBJECT
signals:
    void currentSelectedData(const QVariant& data);
public:
    explicit PwhContrast(QWidget *parent = 0);
    ~PwhContrast();
public:
    void initTreeData(const QVariant& data);
    void load();
    void upChart();
    void downChart();
    void exportPDF();
private:
    bool parseAnalysisFile(const std::vector<taskInfo>& data);
private:
    void setup_more_ui ();
    void set_table();
    void init_table(QTableWidget*);
private:
    Ui::PwhContrast *ui;
};

#endif // PWHCONTRAST_H
