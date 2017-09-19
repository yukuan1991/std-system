#include "StdMain.h"
#include "ui_StdMain.h"
#include <assert.h>
#include <QQuickItem>
#include <QDebug>
#include <base/lang/not_null.h>
#include <QVariant>

StdMain::StdMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StdMain)
{
    ui->setupUi(this);

    const auto index = ui->tabWidget->currentIndex();
    const auto title = "标准工时系统  " + ui->tabWidget->tabText(index);
    setWindowTitle(title);

    connect(ui->tabWidget, &QTabWidget::tabBarClicked, this, &StdMain::onTabClicked);
}

void StdMain::setIoManipulator(std::shared_ptr<IoManipulator> p)
{
    ui->product_family->setIoManipulator (p);
    ui->video_massive->setIoManipulator (p);
    ui->video_trial->setIoManipulator (p);
    ui->mod->setIoManipulator (p);
    ui->most->setIoManipulator (p);
    ui->mtm->setIoManipulator (p);
    ui->data_base->setIoManipulator (p);
    ui->pwh_contrast->setIoManipulator (p);
    ui->approval->setIoManipulator (p);
    ui->pwh_quota->setIoManipulator(p);
}

StdMain::~StdMain()
{
    delete ui;
}

void StdMain::onTabClicked(int index)
{
    const auto title = "标准工时系统  " + ui->tabWidget->tabText(index);
    setWindowTitle(title);
}


