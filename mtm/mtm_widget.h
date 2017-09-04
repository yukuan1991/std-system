#ifndef MTM_WIDGET_H
#define MTM_WIDGET_H

#include <QWidget>
#include <mtm/Qt-Utils/tinyxml2.h>

namespace Ui {
class mtm_widget;
}

class mtm_widget : public QWidget
{
    Q_OBJECT
signals:
    void code_changed (const QVariant&);
    void return_pressed ();
public:
    explicit mtm_widget(QWidget *parent = 0);
    ~mtm_widget();
    void set_std_time_sum(QString&);

    void set_measure_date (const QDate & date);
    QString measure_date () const;

    void set_measure_man (const QString & data);
    QString measure_man () const;

    void set_task_man (const QString & data);
    QString task_man () const;
private:
    void on_button_mtm_uas_confirm_return_clicked();

    void on_button_mtm_uas_backspace_clicked();
private:
    void init();
    void on_mtm_clicked (bool);
    void on_mtm_hover ();
private:
    Ui::mtm_widget *ui;

    std::map<std::string, std::tuple<std::string, std::string, std::string, std::string, unsigned>> mtm_data_;
    tinyxml2::XMLDocument mtm_doc_;
    tinyxml2::XMLElement* mtm_des_;
    tinyxml2::XMLElement* mtm_start_;
    tinyxml2::XMLElement* mtm_content_;
    tinyxml2::XMLElement* mtm_end_;
    tinyxml2::XMLElement* mtm_tmu_;

    static std::map<std::string, int> kv_tmu_;
};

#endif // MTM_WIDGET_H
