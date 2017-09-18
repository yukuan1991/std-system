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
class QMdiSubWindow;
class PwhContrastMain : public QWidget
{
    Q_OBJECT
signals:
    void setIo();
public:
    explicit PwhContrastMain(QWidget *parent = 0);
    ~PwhContrastMain();

    void setIoManipulator (std::shared_ptr<IoManipulator> io) { this->io = io;  emit setIo(); }
private:
    void load();
    void exportPDF();
private:
    void initConn();
    void initTreeDir();
private:
    Ui::PwhContrastMain *ui;
    std::shared_ptr<IoManipulator> io;
};

#endif // PWHCONTRASTMAIN_H
