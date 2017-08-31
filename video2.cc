#include "video2.h"
#include "ui_video2.h"

video2::video2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::video2)
{
    ui->setupUi(this);
}

video2::~video2()
{
    delete ui;
}
