#ifndef MTM_MAIN_H
#define MTM_MAIN_H

#include <QWidget>
#include "Qt-Utils/json.hpp"
#include <base/lang/not_null.h>


namespace Ui {
class mtm_main;
}

class mtm_analysis;
using nlohmann::json;

class mtm_main : public QWidget
{
    Q_OBJECT

public:
    explicit mtm_main(QWidget *parent = 0);
    ~mtm_main();
private:
//    void init();
    void init_conn();
    void set_button_enabled();

private:
    void file_operations(const QString& s);
    void file_new();
    void file_open();
    void file_save();
    void file_save_as();
private:
    void add_row();
    void copy();
    void cut();
    void paste();
    void del();
    void on_measure_date ();
    void on_measure_man ();
    void on_task_man ();
    void help_advice();
private:
    not_null<mtm_analysis*> create_window (const QString & title);
    mtm_analysis* active_window();
private:
    Ui::mtm_main *ui;
    json current_file_data_;

};

#endif // MTM_MAIN_H
