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

//    QVariant data = io->pullData("product");
//    ui->contrastWidget->initTreeData(data);

    initConn();
}

PwhContrastMain::~PwhContrastMain()
{
    delete ui;
}

void PwhContrastMain::load()
{
    ui->contrastWidget->load();
}


void PwhContrastMain::exportPDF()
{
//    auto w = activeWindow();
//    if(w == nullptr)
//    {
//        return;
//    }
//    w->exportPDF();
}

void PwhContrastMain::initConn()
{
    connect(ui->buttonImport, &QPushButton::clicked, this, &PwhContrastMain::load);
    connect(this, &PwhContrastMain::setIo, this, &PwhContrastMain::initTreeDir);
    //    connect(ui->rib, &PwhContrastRibbon::exportPDF, this, &PwhContrastMain::exportPDF);
}

void PwhContrastMain::initTreeDir()
{
    if(io != nullptr)
    {
        const auto data = io->pullData("product");
        ui->contrastWidget->initTreeData(data);
    }
}

