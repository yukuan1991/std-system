#include "most_widget.h"
#include "ui_most_widget.h"
#include <boost/regex.hpp>
#include "utils/Qt-Utils/tinyxml2.h"
#include "utils/arithmetic_resource.hpp"
#include "most_selection_dlg.h"
#include <QMessageBox>
#include <QDate>

std::map<std::string, int> most_widget::kv_tmu_;

most_widget::most_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::most_widget)
{
    ui->setupUi(this);
    init();
    //std::tie (kv_tmu_, most_data_) = read_tmu_data ();
    std::tie (kv_tmu_, std::ignore, std::ignore, std::ignore) = read_tmu_data();
}

most_widget::~most_widget()
{
    delete ui;
}

void most_widget::set_std_time_sum(QString &sum)
{
    ui->label_total->setText(sum);
}

void most_widget::set_measure_date(const QDate &date)
{
    ui->measure_date->setText (date.toString ("yyyy-MM-dd"));
}

QString most_widget::measure_date() const
{
    return ui->measure_date->text ();
}

void most_widget::set_measure_man(const QString &data)
{
    ui->measure_man->setText (data);
}

QString most_widget::measure_man() const
{
    return ui->measure_man->text();
}

void most_widget::set_task_man(const QString &data)
{
    ui->task_man->setText (data);
}

QString most_widget::task_man() const
{
    return ui->task_man->text();
}

void most_widget::on_button_gms_reset_clicked()
{
    for(auto iter : gms_)
    {
        iter->setCurrentIndex (0);
    }
}

void most_widget::on_button_cms_reset_clicked()
{
    for(auto iter : cms_)
    {
        iter->setCurrentIndex (0);
    }
}

void most_widget::on_button_tus_reset_clicked()
{
    for(auto iter : tus_)
    {
        iter->setCurrentIndex (0);
    }

    ui->combo_tus_u_categories->setCurrentIndex (0);
}

void most_widget::on_button_most_backspace_clicked()
{
    emit code_changed (0);
}

void most_widget::on_button_most_confirm_return_clicked()
{
    auto is_selected = [] (const auto& combos)
    {
        for (auto & iter : combos)
        {
            if (iter->currentText () != "0") return true;
        }
        return false;
    };

    decltype (&cms_) group_arr [] = {&cms_, &gms_, &tus_};
    unsigned i = 0;
    decltype (&cms_) selected = nullptr;

    for (auto iter : group_arr)
    {
        if (is_selected (*iter))
        {
            selected = iter;
            i ++;
        }
    }

    if (i != 1)
    {
        if (i > 1)
        {
            QMessageBox::information (this, "enter", "cannot fill up information of more than 1 row/发现多行分析结果，请重置不需要的分析结果");
        }
        else if (i < 1)
        {
            QMessageBox::information (this, "enter", "you need to fill up information of a row to continue/未发现分析结果，请先进行分析");
        }

        return;
    }

    assert (selected);
    QStringList selected_list;
    for (auto & iter : *selected)
    {
        QString single_value;
        if (iter->objectName ().toUpper ().toStdString ().substr (10, 1) == "U")
        {
            single_value += ui->combo_tus_u_categories->currentText ();
        }
        else
        {
            single_value += iter->objectName ().toUpper ().toStdString ().substr (10, 1).data ();
        }
        single_value += iter->currentText ();

        auto prefix_single_value = "most_" + single_value;

        if (kv_tmu_.find (prefix_single_value.toStdString ()) == kv_tmu_.end ())
        {
            QMessageBox::information (this, "data", QString {"invalid data/输入的数据不合法 : "} + single_value);
            return;
        }

        selected_list << prefix_single_value;
    }

    emit code_changed (selected_list);
    emit return_pressed ();
}

void most_widget::init()
{
    auto list_children = children ();

    for (auto & iter : list_children)
    {
        auto obj = dynamic_cast<QComboBox*> (*(&iter));
        if (obj)
        {
            using highlight_fptr = void (QComboBox::*) (const QString&);
            highlight_fptr signal_hightlight = &QComboBox::highlighted;
            connect (obj, signal_hightlight, this, &most_widget::on_most_highlighted);
            using index_change_fptr = void (QComboBox::*) (const QString&);
            index_change_fptr signal_index_change = &QComboBox::currentTextChanged;
            connect (obj, signal_index_change, this, &most_widget::on_most_dot_dot_dot_selected);
        }
    }

    connect(ui->button_most_backspace , &QPushButton::clicked,
            this, &most_widget::on_button_most_backspace_clicked);
    connect(ui->button_most_confirm_return, &QPushButton::clicked,
            this, &most_widget::on_button_most_confirm_return_clicked);
    connect(ui->button_gms_reset, &QPushButton::clicked,
            this, &most_widget::on_button_gms_reset_clicked);
    connect(ui->button_cms_reset, &QPushButton::clicked,
            this, &most_widget::on_button_cms_reset_clicked);
    connect(ui->button_tus_reset, &QPushButton::clicked,
            this, &most_widget::on_button_tus_reset_clicked);


    for (auto & iter : list_children)
    {
        if (iter->objectName ().length () != 13)
        {
            continue;
        }

        auto obj = dynamic_cast<QComboBox*> (&(*iter));

        if (obj)
        {
            if (boost::regex_search (obj->objectName ().toStdString (), boost::regex {"cms"}))
            {
                cms_.emplace_back (obj);
            }
            else if (boost::regex_search (obj->objectName ().toStdString (), boost::regex {"gms"}))
            {
                gms_.emplace_back (obj);
            }
            else if (boost::regex_search (obj->objectName ().toStdString (), boost::regex {"tus"}))
            {
                tus_.emplace_back (obj);
            }
        }
    }
}

void most_widget::on_most_highlighted(const QString &highlight)
{
    auto combo = dynamic_cast<QComboBox*>(sender ());
    assert (combo);
    if (combo->objectName ().length () > 13)
    {
        return;
    }
    assert (combo->objectName ().length () == 13);

    std::string capital_prefix;
    if (combo->objectName ().toStdString ().substr (10, 1) == "u")
    {
        capital_prefix =  ui->combo_tus_u_categories->currentText ().toStdString ();
    }
    else
    {
        capital_prefix = combo->objectName ().toUpper ().toStdString ().substr (10, 1);
    }

    if (highlight == "……")
    {
        ui->text_area_most_description->setText (R"(<img src="icon/greater.png" />)");
        return;
    }

    auto str_key = capital_prefix + highlight.toStdString ();


    auto iter = most_data_.find (str_key);
    if (iter == most_data_.end ())
    {
        return;
    }

    tinyxml2::XMLDocument doc;
    QString qstr_rich_text;

    auto p = doc.NewElement ("p"); assert (p);
    auto span = doc.NewElement ("span"); assert (span);
    p->InsertEndChild (span);
    doc.InsertEndChild (p);

    for (auto &iter_ : iter->second)
    {
        if (iter_.second)
        {
            span->SetAttribute ("style", " font-size:11pt; font-weight:600;");
        }
        else
        {
            span->SetAttribute ("style", "font-size:11pt;");
        }

        span->SetText (iter_.first.data ());
        tinyxml2::XMLPrinter prt;
        doc.Print (&prt); assert (prt.CStr ());
        qstr_rich_text += prt.CStr ();
    }

    ui->text_area_most_description->setText (qstr_rich_text);
}

void most_widget::on_most_dot_dot_dot_selected(const QString &text)
{
    if (text != "……")
    {
        return;
    }

    auto src = sender (); assert (src);
    auto combo = dynamic_cast<QComboBox*>(src); assert (combo);

    most_selection_dlg dlg;
    if (QDialog::Accepted != dlg.exec ())
    {
        combo->setCurrentIndex (0);
        return;
    }

    auto text_clicked = dlg.get_checked_item ();
    combo->setEditText (text_clicked);
}
