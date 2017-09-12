#ifndef PWHCONTRASTMAIN_H
#define PWHCONTRASTMAIN_H

#include <QWidget>
#include <base/lang/not_null.h>
#include "IoManipulator.h"
#include <memory>

namespace Ui {
class PwhContrastMain;
}

class PwhContrast;
class PwhContrastMain : public QWidget
{
    Q_OBJECT
public:
    explicit PwhContrastMain(QWidget *parent = 0);
    ~PwhContrastMain();

    void setIoManipulator (std::shared_ptr<IoManipulator> io) { this->io = io; }

private:
    void fileNew();
private:
    void addFirstTable();
    void addSecondTable();
    void addThirdTable();
    void clearFirstTable();
    void clearSecondTable();
    void clearThirdTable();

    void importAnalysisFile();
    void upChart();
    void downChart();
    void exportPDF();
private:
    void initConn();
private:
    not_null<PwhContrast*> createWindow();
    PwhContrast* activeWindow();
private:
    Ui::PwhContrastMain *ui;
    std::shared_ptr<IoManipulator> io;
};

#endif // PWHCONTRASTMAIN_H
