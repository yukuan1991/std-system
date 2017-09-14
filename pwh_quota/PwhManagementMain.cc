#include "PwhManagementMain.h"
#include "ui_pwhmanagementmain.h"
#include "pwh_quota//PwhManagement.h"
#include <memory>
#include <QMdiSubWindow>

using namespace std;
PwhManagementMain::PwhManagementMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PwhManagementMain)
{
    ui->setupUi(this);
    ui->mdi->setViewMode(QMdiArea::TabbedView);

    initConn();
}

PwhManagementMain::~PwhManagementMain()
{
    delete ui;
}

void PwhManagementMain::fileNew()
{
    auto w = createWindow();
    if (io != null)
    {
        auto var = io->pullData ("product");
        w->initTreeWidget (var);
        w->setIoManipulator(io);
    }
}

void PwhManagementMain::detailedInfo()
{
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    w->on_button_detail_clicked();
}

void PwhManagementMain::modifyClicked()
{
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    w->on_button_modify_clicked();
}

void PwhManagementMain::addStdDatabase()
{
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    w->on_button_addStdDatabase_clicked();
}

void PwhManagementMain::exportPDF()
{
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    w->on_button_exportDF_clicked();
}

void PwhManagementMain::reportHeader()
{
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    w->on_button_reportHeader_clicked();
}

void PwhManagementMain::initConn()
{
    connect(ui->rib, &PwhManagementRibbon::file_new, this, &PwhManagementMain::fileNew);
//    connect(ui->rib, &PwhManagementRibbon::detailedInfoClicked, this, &PwhManagementMain::detailedInfo);
//    connect(ui->rib, &PwhManagementRibbon::modifyClicked, this, &PwhManagementMain::modifyClicked);
    connect(ui->rib, &PwhManagementRibbon::addStdDatabaseClicked, this, &PwhManagementMain::addStdDatabase);
    connect(ui->rib, &PwhManagementRibbon::exportPDFClicked, this, &PwhManagementMain::exportPDF);
    connect(ui->rib, &PwhManagementRibbon::reportHeaderClicked, this, &PwhManagementMain::reportHeader);
}

not_null<PwhManagement *> PwhManagementMain::createWindow()
{
    auto ptr_win = make_unique<PwhManagement> ();

    ptr_win->setAttribute(Qt::WA_DeleteOnClose);

    auto w = ui->mdi->addSubWindow(ptr_win.get());

    w->setWindowState(Qt::WindowMaximized);

    return ptr_win.release();
}

PwhManagement *PwhManagementMain::activeWindow()
{
    if(QMdiSubWindow* activeSubWindow = ui->mdi->activeSubWindow())
    {
        auto w = dynamic_cast<PwhManagement*>(activeSubWindow->widget());
        return w;
    }
    else
    {
        return nullptr;
    }
}
