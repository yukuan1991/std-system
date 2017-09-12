#include "mod_main.h"
#include "ui_mod_main.h"
#include "utils/interface_control/about_us_dlg.h"
#include <QInputDialog>
#include "mod_analysis.h"
#include <memory>
#include <QMdiSubWindow>
#include <QDateEdit>
#include <QFileDialog>
#include <base/io/file/file.hpp>
#include <base/utils/charset.hpp>
#include <QMessageBox>
#include "utils/SaveTreeDialog.h"
#include <QJsonDocument>
#include <QDebug>

using namespace std;

mod_main::mod_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_main)
{
    ui->setupUi(this);
    ui->mdi->setViewMode (QMdiArea::TabbedView);
    setWindowState(Qt::WindowMaximized);
    setMinimumSize(QSize(1000, 800));
    init_conn();
    set_button_enabled();
}

mod_main::~mod_main()
{
    delete ui;
}

void mod_main::init_conn()
{
    connect (ui->widget_ribbon, &ribbon::file_new, this, &mod_main::file_new);
    connect (ui->widget_ribbon, &ribbon::file_open, this, &mod_main::file_open);
    connect (ui->widget_ribbon, &ribbon::file_save, this, &mod_main::file_save);
    connect (ui->widget_ribbon, &ribbon::file_saveas, this, &mod_main::file_save_as);
    connect (ui->widget_ribbon, &ribbon::file_exit, this, &mod_main::close);

    connect(ui->widget_ribbon, &ribbon_mod::copy, this, &mod_main::copy);
    connect(ui->widget_ribbon, &ribbon_mod::cut, this, &mod_main::cut);
    connect(ui->widget_ribbon, &ribbon_mod::paste, this, &mod_main::paste);
    connect(ui->widget_ribbon, &ribbon_mod::del, this, &mod_main::del);
    connect(ui->widget_ribbon, &ribbon_mod::add_row, this, &mod_main::add_row);
    connect(ui->widget_ribbon, &ribbon_mod::measure_date, this, &mod_main::on_measure_date);
    connect(ui->widget_ribbon, &ribbon_mod::measure_man, this, &mod_main::on_measure_man);
    connect(ui->widget_ribbon, &ribbon_mod::task_man, this, &mod_main::on_task_man);

    connect(ui->widget_ribbon, &ribbon_mod::help, this, &mod_main::help_advice);

    connect(ui->mdi, &QMdiArea::subWindowActivated, this, &mod_main::set_button_enabled);

}

void mod_main::set_button_enabled()
{
    const bool state = (active_window() != nullptr);
    ui->widget_ribbon->set_enabled(state);
}

void mod_main::file_operations(const QString &s)
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

void mod_main::file_save()
{
    const auto active = ui->mdi->currentSubWindow ();
    if (active == nullptr)
    {
        return;
    }
    auto w = dynamic_cast<mod_analysis *> (active->widget ());

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

    QByteArray arr (w->dump ().dump (4).data ());
    const auto variantData = QJsonDocument::fromJson (arr).toVariant ();

    io->addNode (path, name, "product", "mod", variantData);
}

void mod_main::file_save_as()
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
        const auto path = QFileDialog::getSaveFileName(this, "文件保存", ".", tr ("Mod Analysis File (*.modaf)"));

        if (path.isEmpty())
        {
            return;
        }

        const auto data = w->dump ();

        active->setWindowTitle(path);
        file::write_buffer (::utf_to_sys (path.toStdString ()).data (), data.dump (4));
    }
}

void mod_main::copy()
{
    auto win = active_window();
    if (win == nullptr)
    {
        return;
    }

    win->copy();
}

void mod_main::cut()
{
    auto win = active_window();
    if (win == nullptr)
    {
        return;
    }

    win->cut();
}

void mod_main::paste()
{
    auto win = active_window();
    if (win == nullptr)
    {
        return;
    }

    win->paste();
}

void mod_main::del()
{
    auto win = active_window();
    if (win == nullptr)
    {
        return;
    }

    win->del();
}

void mod_main::add_row()
{
    auto win = active_window();
    if (win == nullptr)
    {
        return;
    }

    win->add_row();
}


void mod_main::help_advice()
{
    const QString text = R"(<html><head/><body><p>如果您有任何需求与改进建议，</p><p>请随时联系IEToolkit君qq3350436646</p>
                         <p><span style=" font-weight:600; color:red">加好友请扫右边二维码---&gt;</span></p></body></html>)";
    const QString qr_code = R"( <a href = "www.shionto.com"> <img src="./png/about-us.png" width="300" height = "400"/></a>)";
    about_us_dlg::show_info(text, qr_code);
}

void mod_main::on_measure_date()
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

void mod_main::on_measure_man()
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

void mod_main::on_task_man()
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

not_null<mod_analysis *> mod_main::create_window(const QString &title)
{
    auto mod_win = make_unique<mod_analysis> ();
    auto ptr_mod_win = mod_win.get();

    mod_win->setAttribute (Qt::WA_DeleteOnClose);
    auto w = ui->mdi->addSubWindow (ptr_mod_win);
    w->setWindowTitle (title);

    w->setWindowState (Qt::WindowMaximized);

    return mod_win.release ();
}

mod_analysis *mod_main::active_window()
{
    if(QMdiSubWindow* active_subwindow = ui->mdi->activeSubWindow())
    {
        mod_analysis* w = dynamic_cast<mod_analysis*>(active_subwindow->widget());
        return w;
    }
    else
    {
        return nullptr;
    }
}

void mod_main::file_new()
{
    auto w = create_window ("未命名");
    w->set_task_count ();
}

void mod_main::file_open()
{
    const auto path = QFileDialog::getOpenFileName (this, "文件打开", ".", tr ("Mod Analysis File (*.modaf)"));
    if (path.isEmpty ())
    {
        return;
    }

    auto res = file::read_all (::utf_to_sys (path.toStdString ()).data ());
    if (not res)
    {
        QMessageBox::information (this, "打开", "文件无法打开,读取失败");
        return;
    }
    try
    {
        const auto data = json::parse (res.value ());
        auto w = create_window (path);
        w->load (data);
    }
    catch (std::exception &)
    {
        QMessageBox::information (this, "打开", "文件格式错误 无法打开");
        return;
    }
}
