#include "PwhContrastMain.h"
#include "ui_pwhcontrastmain.h"
#include <memory>
#include "pwh_contrast/PwhContrast.h"
#include <QMdiSubWindow>
#include "pwh_contrast/ribbon/PwhContrastRibbon.h"
#include <QDebug>

using namespace std;

PwhContrastMain::PwhContrastMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PwhContrastMain)
{
    ui->setupUi(this);
    ui->mdi->setViewMode(QMdiArea::TabbedView);

    initConn();
}

PwhContrastMain::~PwhContrastMain()
{
    delete ui;
}

void PwhContrastMain::fileNew()
{
    auto w = createWindow();
    if (io != null)
    {
        auto var = io->pullData ("product");
        w->initTreeData (var);
    }
}

void PwhContrastMain::load()
{
    qDebug() << "addchart";
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }
    w->load();
}

//void PwhContrastMain::upChart()
//{
//    qDebug() << "upchart";
//    auto w = activeWindow();
//    if(w == nullptr)
//    {
//        return;
//    }
//    w->upChart();
//}

//void PwhContrastMain::downChart()
//{
//    qDebug() << "downchart";
//    auto w = activeWindow();
//    if(w == nullptr)
//    {
//        return;
//    }
//    w->downChart();
//}

void PwhContrastMain::exportPDF()
{
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }
    w->exportPDF();
}

void PwhContrastMain::initConn()
{
    connect(ui->rib, &ribbon::file_new, this, &PwhContrastMain::fileNew);

    connect(ui->rib, &PwhContrastRibbon::importAnalysisFile, this, &PwhContrastMain::load);
//    connect(ui->rib, &PwhContrastRibbon::upChart, this, &PwhContrastMain::upChart);
//    connect(ui->rib, &PwhContrastRibbon::downChart, this, &PwhContrastMain::downChart);
    connect(ui->rib, &PwhContrastRibbon::exportPDF, this, &PwhContrastMain::exportPDF);

}

not_null<PwhContrast *> PwhContrastMain::createWindow()
{
    auto pwh_win = make_unique<PwhContrast> ();
    pwh_win->setAttribute(Qt::WA_DeleteOnClose);
    auto w = ui->mdi->addSubWindow (pwh_win.get());

    w->setWindowState(Qt::WindowMaximized);
    return pwh_win.release();
}

PwhContrast *PwhContrastMain::activeWindow()
{
    if(QMdiSubWindow* active_window = ui->mdi->activeSubWindow())
    {
        PwhContrast* w = dynamic_cast<PwhContrast*>(active_window->widget());
        return w;
    }
    else
    {
        return nullptr;
    }

}
