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
    createWindow();
}

void PwhContrastMain::addFirstTable()
{
    qDebug() << "addFirstTable";
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    w->on_add_clicked();
}

void PwhContrastMain::addSecondTable()
{
    qDebug() << "addSecondTable";
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    w->on_add_2_clicked();
}

void PwhContrastMain::addThirdTable()
{
    qDebug() << "addThirdTable";
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    w->on_add_3_clicked();
}

void PwhContrastMain::clearFirstTable()
{
    qDebug() << "clearFirstTable";
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    w->on_delete_2_clicked();
}

void PwhContrastMain::clearSecondTable()
{
    qDebug() << "clearSecondTable";
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    w->on_delete_3_clicked();

}

void PwhContrastMain::clearThirdTable()
{
    qDebug() << "clearThirdTable";
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }

    w->on_delete_4_clicked();
}

void PwhContrastMain::importAnalysisFile()
{
    qDebug() << "addchart";
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }
    w->importAnalysisFile();
}

void PwhContrastMain::upChart()
{
    qDebug() << "upchart";
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }
    w->upChart();
}

void PwhContrastMain::downChart()
{
    qDebug() << "downchart";
    auto w = activeWindow();
    if(w == nullptr)
    {
        return;
    }
    w->downChart();
}

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

    connect(ui->rib, &PwhContrastRibbon::importAnalysisFile, this, &PwhContrastMain::importAnalysisFile);
    connect(ui->rib, &PwhContrastRibbon::upChart, this, &PwhContrastMain::upChart);
    connect(ui->rib, &PwhContrastRibbon::downChart, this, &PwhContrastMain::downChart);
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
