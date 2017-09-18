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

    initConn();

}

PwhManagementMain::~PwhManagementMain()
{
    delete ui;
}

void PwhManagementMain::addStdDatabase()
{
    if(ui->quotaWidget == nullptr)
    {
        return;
    }
    ui->quotaWidget->on_button_addStdDatabase_clicked();
}

void PwhManagementMain::reportHeader()
{
    if(ui->quotaWidget == nullptr)
    {
        return;
    }
    ui->quotaWidget->on_button_reportHeader_clicked();
}

void PwhManagementMain::initConn()
{
    connect(this, &PwhManagementMain::setIo, this, &PwhManagementMain::initTreeDir);
    connect(ui->buttonAddStdTime, &QPushButton::clicked, this, &PwhManagementMain::addStdDatabase);
    connect(ui->buttonSettingTitle, &QPushButton::clicked, this, &PwhManagementMain::reportHeader);
}

void PwhManagementMain::initTreeDir()
{
    if(io != nullptr)
    {
        const auto data = io->pullData("product");
        ui->quotaWidget->initTreeWidget(data);
        ui->quotaWidget->setIoManipulator(io);
    }
}


