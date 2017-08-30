#include "StdMain.h"
#include "ui_StdMain.h"
#include <assert.h>
#include <QQuickItem>
#include <QDebug>

StdMain::StdMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StdMain)
{
    ui->setupUi(this);
    auto root = ui->topBanner->rootObject ();
    assert (root);
}

StdMain::~StdMain()
{
    delete ui;
}

void StdMain::onPosChanged(int x, int y)
{
    const auto oldPos = pos ();
    const auto offset = QPoint (x, y);
    this->move (oldPos + offset);
}

