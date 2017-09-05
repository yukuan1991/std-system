#ifndef MOD_ANALYSIS_H
#define MOD_ANALYSIS_H

#include <QWidget>
#include "utils/json.hpp"


namespace Ui {
class mod_analysis;
}

using nlohmann::json;

class mod_analysis : public QWidget
{
    Q_OBJECT
signals:
    void copy();
    void cut();
    void paste();
    void del();
public:
    explicit mod_analysis(QWidget *parent = 0);
    ~mod_analysis();


    void set_task_count ();
    bool task_content_check ();
    void add_row();

    void set_measure_date (const QDate & date);
    QString measure_date () const;

    void set_measure_man (const QString & data);
    QString measure_man () const;

    void set_task_man (const QString & data);
    QString task_man () const;

    QString std_time_sum () const;

    json dump();
    void load (const json& data);
private:
    void init();
    void init_conn();

private:
    Ui::mod_analysis *ui;

    json current_file_data_;
};

#endif // MOD_ANALYSIS_H
