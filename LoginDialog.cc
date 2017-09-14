#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QVariantMap>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect (ui->login, &QPushButton::clicked, this, &QDialog::accept);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QVariant LoginDialog::dump() const
{
    QVariantMap map;
    map ["user"] = ui->user->text ();
    map ["pass"] = ui->pass->text ();
    return map;
}
