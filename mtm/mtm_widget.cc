#include "mtm_widget.h"
#include "ui_mtm_widget.h"
#include <assert.h>
#include "arithmetic_resource.hpp"
#include <QDate>

std::map<std::string, int> mtm_widget::kv_tmu_;

mtm_widget::mtm_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mtm_widget)
{
    ui->setupUi(this);
    init ();
    std::tie (kv_tmu_, mtm_data_) = read_tmu_data ();
    ui->pushButton_78->setFlat(true);
}


mtm_widget::~mtm_widget()
{
    delete ui;
}

void mtm_widget::set_std_time_sum(QString &sum)
{
    ui->label_total->setText(sum);
}

void mtm_widget::set_measure_date(const QDate &date)
{
    ui->measure_date->setText (date.toString ("yyyy-MM-dd"));
}

QString mtm_widget::measure_date() const
{
    return ui->measure_date->text ();
}

void mtm_widget::set_measure_man(const QString &data)
{
    ui->measure_man->setText (data);
}

QString mtm_widget::measure_man() const
{
    return ui->measure_man->text();
}

void mtm_widget::set_task_man(const QString &data)
{
    ui->task_man->setText (data);
}

QString mtm_widget::task_man() const
{
    return ui->task_man->text();
}

void mtm_widget::on_button_mtm_uas_confirm_return_clicked()
{
    emit return_pressed ();
}

void mtm_widget::on_button_mtm_uas_backspace_clicked()
{
    emit code_changed (1);
}

void mtm_widget::init()
{
    auto list = children ();

    for (auto & iter : list)
    {
        if (strcmp (iter->metaObject ()->className (), "push_button") == 0)
        {
            auto obj = dynamic_cast<push_button*> (*(&iter)); assert (obj);

            connect (obj, &push_button::mouse_enter, this, &mtm_widget::on_mtm_hover);
            connect (obj, &push_button::clicked, this, &mtm_widget::on_mtm_clicked);
        }
    }

    connect(ui->button_mtm_uas_backspace , &QPushButton::clicked,
            this, &mtm_widget::on_button_mtm_uas_backspace_clicked);
    connect(ui->button_mtm_uas_confirm_return, &QPushButton::clicked,
            this, &mtm_widget::on_button_mtm_uas_confirm_return_clicked);

    auto p = mtm_doc_.NewElement ("p"); assert (p);
    auto span = mtm_doc_.NewElement ("span"); assert (span);
    p->InsertEndChild (span);

    auto lambda_add_content = [&] (auto& str, auto&& tracer)
    {
        auto p = mtm_doc_.NewElement ("p"); assert (p);
        auto span = mtm_doc_.NewElement ("span"); assert (span);
        mtm_doc_.InsertEndChild (p);
        p->InsertEndChild (span);
        p->SetAttribute ("align", "center");
        span->SetAttribute ("style", " font-size:12pt; font-weight:600; text-align:center;");
        span->SetText (str);

        p = mtm_doc_.NewElement ("p"); assert (p);
        mtm_doc_.InsertEndChild (p);
        span = mtm_doc_.NewElement ("span"); assert (span);
        p->InsertFirstChild (span);
        span->SetAttribute ("style", "font-size:9pt;");
        tracer = span;
    };

    lambda_add_content ("描述", mtm_des_);
    lambda_add_content ("开始", mtm_start_);
    lambda_add_content ("包含内容", mtm_content_);
    lambda_add_content ("结束", mtm_end_);
    lambda_add_content ("TMU", mtm_tmu_);

    ui->text_area_description->setText ("");
}

void mtm_widget::on_mtm_clicked(bool)
{
    QObject* src = sender (); assert (src);
    push_button* button = dynamic_cast<push_button*>(src); assert (button);
    QByteArray arr {("mtm_" + button->text ()).toStdString ().data ()};
    emit code_changed (arr);
}

void mtm_widget::on_mtm_hover()
{
    auto obj = sender (); assert (obj);
    push_button* btn = dynamic_cast<push_button*>(obj); assert (btn);

    mtm_des_->SetText (std::get<0>(mtm_data_[btn->text ().toStdString ()]).data ());
    mtm_start_->SetText (std::get<1>(mtm_data_[btn->text ().toStdString ()]).data ());
    mtm_content_->SetText (std::get<2>(mtm_data_[btn->text ().toStdString ()]).data ());
    mtm_end_->SetText (std::get<3>(mtm_data_[btn->text ().toStdString ()]).data ());
    mtm_tmu_->SetText (std::get<4>(mtm_data_[btn->text ().toStdString ()]));
    tinyxml2::XMLPrinter prt;
    mtm_doc_.Print (&prt);
    ui->text_area_description->setText (prt.CStr ());
}
