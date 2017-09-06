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
}

StdMain::~StdMain()
{
    delete ui;
}

