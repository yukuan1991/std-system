#ifndef PWHMANAGEMENTMAIN_H
#define PWHMANAGEMENTMAIN_H

#include <QWidget>
#include <base/lang/not_null.h>
#include "IoManipulator.h"
#include <memory>
namespace Ui {
class PwhManagementMain;
}

class PwhManagement;
class QMdiSubWindow;
class PwhManagementMain : public QWidget
{
    Q_OBJECT
signals:
    setIo();
public:
    explicit PwhManagementMain(QWidget *parent = 0);
    ~PwhManagementMain();

    void setIoManipulator (std::shared_ptr<IoManipulator> io) { this->io = io; emit setIo(); }
private:
    void fileNew();
private:
    void detailedInfo();
    void modifyClicked();
    void addStdDatabase();
    void exportPDF();
    void reportHeader();
private:
    void initConn();
    void initTreeDir();
    void mdi_changed (QMdiSubWindow *window);
private:
    not_null<PwhManagement*> createWindow();
    PwhManagement* activeWindow();
private:
    Ui::PwhManagementMain *ui;
    std::shared_ptr<IoManipulator> io;
};

#endif // PWHMANAGEMENTMAIN_H
