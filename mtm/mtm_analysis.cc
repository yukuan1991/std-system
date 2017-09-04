#include "mtm_analysis.h"
#include "ui_mtm_analysis.h"
#include <QInputDialog>
#include <QDate>

mtm_analysis::mtm_analysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mtm_analysis)
{
    ui->setupUi(this);
    init();
    init_conn();
}

mtm_analysis::~mtm_analysis()
{
    delete ui;
}

void mtm_analysis::set_task_count()
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

bool mtm_analysis::task_content_check()
{
    return ui->widget_data->task_content_check();
}

void mtm_analysis::add_row()
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

void mtm_analysis::init()
{
    ui->widget_data->set_unit(0.036);
}

void mtm_analysis::init_conn()
{
    connect (ui->widget_mtm, &mtm_widget::code_changed,
             ui->widget_data, &data_widget::add_code);

    connect (ui->widget_mtm, &mtm_widget::return_pressed,
             ui->widget_data, &data_widget::next_code);

    connect(this, &mtm_analysis::cut, ui->widget_data, &data_widget::on_cut);
    connect(this, &mtm_analysis::copy, ui->widget_data, &data_widget::on_copy);
    connect(this, &mtm_analysis::paste, ui->widget_data, &data_widget::on_paste);
    connect(this, &mtm_analysis::del, ui->widget_data, &data_widget::on_del);

    connect (ui->widget_data, &data_widget::std_time_sum,
             ui->widget_mtm, &mtm_widget::set_std_time_sum);
}

void mtm_analysis::set_measure_date(const QDate &date)
{
    ui->widget_mtm->set_measure_date(date);
}

QString mtm_analysis::measure_date() const
{
    return ui->widget_mtm->measure_date();
}

void mtm_analysis::set_measure_man(const QString &data)
{
    ui->widget_mtm->set_measure_man(data);
}

QString mtm_analysis::measure_man() const
{
    return ui->widget_mtm->measure_man();
}

void mtm_analysis::set_task_man(const QString &data)
{
    ui->widget_mtm->set_task_man(data);
}

QString mtm_analysis::task_man() const
{
    return ui->widget_mtm->task_man();
}

nlohmann::json mtm_analysis::dump()
{
    json data;
    data ["form"]["总计"] = ui->widget_data->save_result();

    data ["measure-date"] = measure_date().toStdString ();
    data ["measure-man"] = measure_man().toStdString ();
    data ["task-man"] = task_man().toStdString ();
//    data ["std-time"] = std_time_sum().toStdString();

    return data;
}

void mtm_analysis::load(const nlohmann::json &data)
{
    const auto iter_form = data.find ("form");
    assert (iter_form != end (data));
    assert (iter_form->is_object ());
    auto iter_result = iter_form->find ("总计");
    assert (iter_result != iter_form->end () and iter_result->is_array ());

    ui->widget_data->set_row (static_cast<int> (iter_result->size ()));
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
