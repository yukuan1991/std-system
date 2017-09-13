#include "mod_widget.h"
#include "ui_mod_widget.h"
#include <assert.h>
#include "utils/arithmetic_resource.hpp"
#include <QDate>

std::map<std::string, int> mod_widget::kv_tmu_;

mod_widget::mod_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_widget)
{
    ui->setupUi(this);

    init ();
    std::tie (kv_tmu_, std::ignore, mod_data_, std::ignore) = read_tmu_data();
}

mod_widget::~mod_widget()
{
    delete ui;
}

void mod_widget::set_std_time_sum (QString &sum)
{
    ui->label_total->setText (sum);
}

void mod_widget::set_measure_date(const QDate &date)
{
    ui->measure_date->setText (date.toString ("yyyy-MM-dd"));
}

QString mod_widget::measure_date () const
{
    return ui->measure_date->text ();
}

void mod_widget::set_measure_man(const QString &data)
{
    ui->measure_man->setText (data);
}

QString mod_widget::measure_man() const
{
    return ui->measure_man->text();
}

void mod_widget::set_task_man(const QString &data)
{
    ui->task_man->setText (data);
}

QString mod_widget::task_man() const
{
    return ui->task_man->text();
}

//double mod_widget::current_unit()
//{
//    return 0.129;
//}

void mod_widget::on_button_mod_confirm_return_clicked()
{
    emit return_pressed ();
}

void mod_widget::on_button_mod_backspace_clicked()
{
    emit code_changed (1);
}

void mod_widget::init()
{
    auto list = children();
    for (auto & iter : list)
    {
        push_button* button = dynamic_cast<push_button*>(iter);
        if (button)
        {
            connect (button, &push_button::mouse_enter, this, &mod_widget::on_mod_hover);
            connect (button, &push_button::clicked, this, &mod_widget::on_mod_clicked);
        }
    }

    connect(ui->button_mod_backspace, &QPushButton::clicked,
            this, &mod_widget::on_button_mod_backspace_clicked);
    connect(ui->button_mod_confirm_return, &QPushButton::clicked,
            this, &mod_widget::on_button_mod_confirm_return_clicked);

    init_xml ();
}

void mod_widget::init_xml()
{
    auto lambda_add = [&] (auto& content, auto& ptr)
    {
        tinyxml2::XMLElement* p = mod_doc_.NewElement ("p");
        mod_doc_.InsertEndChild (p);
        p->SetAttribute ("style", R"(margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;)");
        tinyxml2::XMLElement* span = mod_doc_.NewElement ("span");
        span->SetAttribute ("style", "font-size:11pt; font-weight:600;");
        p->InsertEndChild (span);
        p->InsertEndChild (mod_doc_.NewElement ("br"));
        span->SetText (content);
        span = mod_doc_.NewElement ("span");
        span->SetAttribute ("style", "font-size:11pt;");
        p->InsertEndChild (span);
        ptr = span;
    };

    lambda_add ("动作属性", mod_attr_);
    lambda_add ("动作名称", mod_name_);
    lambda_add ("动作含义", mod_content_);
    lambda_add ("举例", mod_example_);
    lambda_add ("备注", mod_remark_);
}

void mod_widget::on_mod_hover()
{
    auto src = sender (); assert (src);
    push_button* button = dynamic_cast<push_button*>(src); assert (button);

    auto iter = mod_data_.find (button->text ().toStdString ());
    assert (iter != mod_data_.end ());
    std::string& attr = std::get<0> (iter->second);
    std::string& name = std::get<1> (iter->second);
    std::string& content = std::get<2> (iter->second);
    std::string& example = std::get<3> (iter->second);
    std::string& remark = std::get<4> (iter->second);

    mod_attr_->SetText (attr.data ());
    mod_name_->SetText (name.data ());
    mod_content_->SetText (content.data ());
    mod_example_->SetText (example.data ());
    mod_remark_->SetText (remark.data ());

    tinyxml2::XMLPrinter prt;
    mod_doc_.Print (&prt);
    const auto text = prt.CStr ();

    ui->text_area_mod_description->setText(text);
}

void mod_widget::on_mod_clicked()
{
    QObject* src = sender (); assert (src);
    push_button* button = dynamic_cast<push_button*>(src); assert (button);
    QByteArray arr {("mod_" + button->text ()).toStdString ().data ()};
    emit code_changed (arr);
}
