﻿#include "most_main.h"
#include "ui_most_main.h"
#include "utils/interface_control/about_us_dlg.h"
#include <memory>
#include <QMdiSubWindow>
#include <QDateEdit>
#include <QInputDialog>
#include <base/io/file/file.hpp>
#include <base/utils/charset.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include "utils/SaveTreeDialog.h"
#include <QJsonDocument>
#include "utils/OpenTreeDialog.h"

#include <QDebug>

using namespace std;

most_main::most_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::most_main)
{
    ui->setupUi(this);
    ui->mdi->setViewMode (QMdiArea::TabbedView);
    setWindowState(Qt::WindowMaximized);
    setMinimumSize(QSize(1000, 800));
    init_conn();
    set_button_enabled();
}

most_main::~most_main()
{
    delete ui;
}

void most_main::init_conn()
{
    connect (ui->widget_ribbon, &ribbon::file_new, this, &most_main::file_new);
    connect (ui->widget_ribbon, &ribbon::file_open, this, &most_main::file_open);
    connect (ui->widget_ribbon, &ribbon::file_save, this, &most_main::file_save);

    connect(ui->widget_ribbon, &ribbon_most::copy, this, &most_main::copy);
    connect(ui->widget_ribbon, &ribbon_most::cut, this, &most_main::cut);
    connect(ui->widget_ribbon, &ribbon_most::paste, this, &most_main::paste);
    connect(ui->widget_ribbon, &ribbon_most::del, this, &most_main::del);
    connect(ui->widget_ribbon, &ribbon_most::add_row, this, &most_main::add_row);
    connect(ui->widget_ribbon, &ribbon_most::measure_date, this, &most_main::on_measure_date);
    connect(ui->widget_ribbon, &ribbon_most::measure_man, this, &most_main::on_measure_man);
    connect(ui->widget_ribbon, &ribbon_most::task_man, this, &most_main::on_task_man);

    connect(ui->mdi, &QMdiArea::subWindowActivated, this, &most_main::set_button_enabled);
}

void most_main::set_button_enabled()
{
    const bool state = (active_window() != nullptr);
    ui->widget_ribbon->set_enabled(state);
}

void most_main::file_operations(const QString &s)
{
    if(s == "新建")
    {
        file_new();
    }
    else if(s == "打开")
    {
        file_open();
    }
    else if(s == "保存")
    {
        file_save();
    }
    else if(s == "另存为")
    {
        file_save_as();
    }
    else if(s == "退出")
    {
        close();
    }
}

void most_main::file_new()
{
    auto w = create_window ("未命名");
    w->set_task_count ();
}

void most_main::file_open()
{
    OpenTreeDialog dlg;
    dlg.load(io->pullData("product"));

    if(dlg.exec() == QDialog::Accepted)
    {
        if(dlg.type() != "most")
        {
            QMessageBox::information(this, "提示", "文件选取错误，请选择正确的文件！");
            return;
        }
        const auto content =  dlg.dump().toMap()["content"];
        const auto name = dlg.dump().toMap()["name"].toString();
        const auto data = QJsonDocument::fromVariant(content).toJson().toStdString();

        auto w = create_window(name);
        w->load(nlohmann::json::parse (data));
    }
}

void most_main::file_save()
{
    const auto active = ui->mdi->currentSubWindow ();
    if (active == nullptr)
    {
        return;
    }
    auto w = dynamic_cast<most_analysis *> (active->widget ());

    if (w == nullptr)
    {
        return;
    }

    if (!w->task_content_check ())
    {
        return;
    }

    const auto data = io->pullData ("product");

    SaveTreeDialog dlg;
    dlg.load (data);
    const auto res = dlg.exec ();
    if (res != SaveTreeDialog::Accepted)
    {
        return;
    }

    const auto saveDetail = dlg.dump ().toMap ();
    const auto path = saveDetail["path"].toStringList ();
    const auto name = saveDetail["name"].toString ();

    ui->mdi->activeSubWindow()->setWindowTitle(name);

    QByteArray arr (w->dump ().dump (4).data ());
    const auto variantData = QJsonDocument::fromJson (arr).toVariant ();

    QVariantList list;
    for (auto & it : path)
    {
        list << it;
    }
    QVariantMap map;
    map ["path"] = list;
    map ["file"] = "product";
    map ["name"] = name;
    map ["data"] = variantData;
    map ["type"] = "most";

    QVariantMap totalMap;
    totalMap["raw"] = map;
    totalMap["类型"] = "most";
    totalMap["提交人"] = io->user ();
    totalMap["提交到"] = "product";
    totalMap["name"] = name;
    totalMap["content"] = variantData;

    io->doPost ("add-approv", totalMap);
}

void most_main::file_save_as()
{
    const auto active = ui->mdi->currentSubWindow ();
    if (active == nullptr)
    {
        return;
    }

    auto w = active_window ();

    if (!w->task_content_check ())
    {
        return;
    }

    if (w != nullptr)
    {
        const auto path = QFileDialog::getSaveFileName(this, "文件保存", ".", tr ("Most Analysis File (*.mostaf)"));
        if(path.isEmpty())
        {
            return;
        }

        const auto data = w->dump ();

        active->setWindowTitle(path);
        file::write_buffer (::utf_to_sys (path.toStdString ()).data (), data.dump (4));
    }
}

void most_main::copy()
{
    auto w = active_window();
    if(w == nullptr)
    {
        return;
    }
    w->copy();
}

void most_main::cut()
{
    auto w = active_window();
    if(w == nullptr)
    {
        return;
    }
    w->cut();
}

void most_main::paste()
{
    auto w = active_window();
    if(w == nullptr)
    {
        return;
    }
    w->paste();
}

void most_main::del()
{
    auto w = active_window();
    if(w == nullptr)
    {
        return;
    }
    w->del();
}

void most_main::add_row()
{
    auto w = active_window();
    if(w == nullptr)
    {
        return;
    }
    w->add_row();
}

void most_main::on_measure_date()
{
    auto w = active_window ();
    if (w == nullptr)
    {
        return;
    }

    QDialog dlg (this);

    auto edit = new QDateEdit (&dlg);
    edit->setCalendarPopup (true);
    edit->setDate (QDate::currentDate ());

    auto ok_button = new QPushButton (&dlg);
    ok_button->setText ("确定");

    auto layout = new QHBoxLayout;

    layout->addWidget (edit);
    layout->addWidget (ok_button);
    dlg.setLayout (layout);

    connect (ok_button, &QPushButton::clicked, &dlg, &QDialog::accept);
    const auto res = dlg.exec ();

    if (res != QDialog::Accepted)
    {
        return;
    }

    w->set_measure_date (edit->date ());
}

void most_main::on_measure_man()
{
    auto w = active_window ();
    if (w == nullptr)
    {
        return;
    }

    bool is_ok;
    const auto old_data = w->measure_man ();
    const auto data = QInputDialog::getText (this, "测量人", "测量人", QLineEdit::Normal, old_data, &is_ok);
    if (is_ok)
    {
        w->set_measure_man (data);
    }
}

void most_main::on_task_man()
{
    auto w = active_window ();
    if (w == nullptr)
    {
        return;
    }

    bool is_ok;
    const auto old_data = w->task_man ();
    const auto data = QInputDialog::getText (this, "作业员", "作业员", QLineEdit::Normal, old_data, &is_ok);

    if (is_ok)
    {
        w->set_task_man (data);
    }
}

void most_main::help_advice()
{
    const QString text = R"(<html><head/><body><p>如果您有任何需求与改进建议，</p><p>请随时联系IEToolkit君qq3350436646</p>
                         <p><span style=" font-weight:600; color:red">加好友请扫右边二维码---&gt;</span></p></body></html>)";
    const QString qr_code = R"( <a href = "www.shionto.com"> <img src="./png/about-us.png" width="300" height = "400"/></a>)";
    about_us_dlg::show_info(text, qr_code);
}

not_null<most_analysis *> most_main::create_window(const QString &title)
{
    auto most_win = make_unique<most_analysis> ();
    auto ptr_most_win = most_win.get();

    most_win->setAttribute (Qt::WA_DeleteOnClose);
    auto w = ui->mdi->addSubWindow (ptr_most_win);
    w->setWindowTitle (title);

    w->setWindowState (Qt::WindowMaximized);

    return most_win.release ();
}

most_analysis *most_main::active_window()
{
    if(QMdiSubWindow* active_subwindow = ui->mdi->activeSubWindow())
    {
        most_analysis* w = dynamic_cast<most_analysis*>(active_subwindow->widget());
        return w;
    }
    else
    {
        return nullptr;
    }
}
