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
    auto topRoot = ui->topBanner->rootObject ();
    auto leftRoot = ui->leftBanner->rootObject ();
    assert (topRoot != null);
    assert (leftRoot != null);
    connect(leftRoot , SIGNAL(stackChanged(QString)) , this , SLOT(onstackChanged(QString)));
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

void StdMain::onstackChanged(QString name)
{
    if(name == "videoMassProduction")
    {
        ui->mainStack->setCurrentWidget (ui->vid);
    }
    else if(name == "mtm")
    {
        ui->mainStack->setCurrentWidget (ui->mtm);
    }
}

