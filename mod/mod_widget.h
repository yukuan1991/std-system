#ifndef MOD_WIDGET_H
#define MOD_WIDGET_H

#include <QWidget>
#include <utils/Qt-Utils/tinyxml2.h>

class QComboBox;
namespace Ui {
class mod_widget;
}

class mod_widget : public QWidget
{
    Q_OBJECT
signals:
    void code_changed (const QVariant&);
    void unit_changed (double);
    void return_pressed ();
public:
    explicit mod_widget(QWidget *parent = 0);
    ~mod_widget();

    double current_unit ();
    void set_std_time_sum(QString&);

    void set_measure_date (const QDate & date);
    QString measure_date () const;

    void set_measure_man (const QString & data);
    QString measure_man () const;

    void set_task_man (const QString & data);
    QString task_man () const;
private:
    void on_button_mod_confirm_return_clicked();

    void on_button_mod_backspace_clicked();
private:
    void init();
    void init_xml ();
    void on_mod_hover ();
    void on_mod_clicked ();

private:
    Ui::mod_widget *ui;

    std::map<std::string, std::tuple<std::string, std::string, std::string, std::string, std::string>> mod_data_;
    tinyxml2::XMLDocument mod_doc_;
    tinyxml2::XMLElement* mod_attr_ = nullptr;
    tinyxml2::XMLElement* mod_name_ = nullptr;
    tinyxml2::XMLElement* mod_content_ = nullptr;
    tinyxml2::XMLElement* mod_example_ = nullptr;
    tinyxml2::XMLElement* mod_remark_ = nullptr;

    static std::map<std::string, int> kv_tmu_;
};

#endif // MOD_WIDGET_H
