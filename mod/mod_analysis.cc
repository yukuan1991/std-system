#include "mod_analysis.h"
#include "ui_mod_analysis.h"
#include <QInputDialog>
#include <QDate>

mod_analysis::mod_analysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_analysis)
{
    ui->setupUi(this);
    init();
    init_conn();
}

mod_analysis::~mod_analysis()
{
    delete ui;
}

void mod_analysis::init()
{
    ui->widget_data->set_unit (0.129);
}

void mod_analysis::init_conn()
{
    connect (ui->widget_mod, &mod_widget::code_changed, ui->widget_data, &mod_data_widget::add_code);
    connect (ui->widget_mod, &mod_widget::unit_changed, ui->widget_data, &mod_data_widget::set_unit);
    connect (ui->widget_mod, &mod_widget::return_pressed, ui->widget_data, &mod_data_widget::next_code);

    connect(this, &mod_analysis::cut, ui->widget_data, &mod_data_widget::on_cut);
    connect(this, &mod_analysis::copy, ui->widget_data, &mod_data_widget::on_copy);
    connect(this, &mod_analysis::paste, ui->widget_data, &mod_data_widget::on_paste);
    connect(this, &mod_analysis::del, ui->widget_data, &mod_data_widget::on_del);

    connect (ui->widget_data, &mod_data_widget::std_time_sum,
             ui->widget_mod, &mod_widget::set_std_time_sum);
}

void mod_analysis::set_task_count()
{
    QInputDialog dlg;
    dlg.setWindowTitle ("调整步数");
    dlg.setLabelText ("请输入工作步数");
    dlg.setOkButtonText ("确 定");
    dlg.setCancelButtonText ("取 消");
    dlg.setInputMode (QInputDialog::IntInput);
    dlg.setIntRange (0, 10000);

    if (dlg.exec () == QDialog::Accepted)
    {
        auto row = dlg.intValue ();
        ui->widget_data->clear ();
        ui->widget_data->set_row (row);

        current_file_data_.clear ();
    }
}

bool mod_analysis::task_content_check()
{
    return ui->widget_data->task_content_check();
}

void mod_analysis::add_row()
{
    QInputDialog dlg;
    dlg.setWindowTitle ("调整步数");
    dlg.setLabelText ("请输入工作步数");
    dlg.setOkButtonText ("确 定");
    dlg.setCancelButtonText ("取 消");
    dlg.setInputMode (QInputDialog::IntInput);
    dlg.setIntRange (0, 10000);

    if (dlg.exec () == QDialog::Accepted)
    {
        auto row = dlg.intValue ();
        ui->widget_data->set_row (row);
    }
}

void mod_analysis::set_measure_date(const QDate &date)
{
    ui->widget_mod->set_measure_date(date);
}

QString mod_analysis::measure_date() const
{
    return ui->widget_mod->measure_date();
}

void mod_analysis::set_measure_man(const QString &data)
{
    ui->widget_mod->set_measure_man(data);
}

QString mod_analysis::measure_man() const
{
    return ui->widget_mod->measure_man();
}

void mod_analysis::set_task_man(const QString &data)
{
    ui->widget_mod->set_task_man(data);
}

QString mod_analysis::task_man() const
{
    return ui->widget_mod->task_man();
}

QString mod_analysis::std_time_sum() const
{
    return ui->widget_data->get_std_time_sum();
}

nlohmann::json mod_analysis::dump()
{
    json data;
    data ["form"] = ui->widget_data->json_data ();

    data ["measure-date"] = measure_date().toStdString ();
    data ["measure-man"] = measure_man().toStdString ();
    data ["task-man"] = task_man().toStdString ();
    data ["std-time"] = std_time_sum().toStdString();

    return data;
}

void mod_analysis::load(const nlohmann::json &data)
{
    const auto iter_form = data.find ("form");
    assert (iter_form != end (data));
    assert (iter_form->is_object ());
    auto iter_right = iter_form->find ("右手");
    assert (iter_right != iter_form->end ());
    assert (iter_right->is_array ());
    auto iter_left = iter_form->find ("左手");
    assert (iter_left != iter_form->end () and iter_left->is_array ());
    auto iter_result = iter_form->find ("总计");
    assert (iter_result != iter_form->end () and iter_result->is_array ());

    ui->widget_data->set_row (static_cast<int> (iter_left->size ()));
    ui->widget_data->load_left (*iter_left);
    ui->widget_data->load_right (*iter_right);
    ui->widget_data->load_result (*iter_result);

    const auto measure_date = data.find ("measure-date");
    if (measure_date != end (data) and measure_date->is_string ())
    {
        auto date = QString::fromStdString (*measure_date);
        set_measure_date (QDate::fromString(date, "yyyy-MM-dd"));
    }
    const auto measure_man = data.find ("measure-man");
    if (measure_man != end (data) and measure_man->is_string ())
    {
        set_measure_man (QString::fromStdString (*measure_man));
    }
    const auto task_man = data.find ("task-man");
    if (task_man != end (data) and task_man->is_string ())
    {
        set_task_man (QString::fromStdString (*task_man));
    }
}


