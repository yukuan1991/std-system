#ifndef MOD_MAIN_H
#define MOD_MAIN_H

#include <QWidget>
#include "utils/json.hpp"
#include <base/lang/not_null.h>


namespace Ui {
class mod_main;
}

class mod_analysis;
using nlohmann::json;

class mod_main : public QWidget
{
    Q_OBJECT
public:
    explicit mod_main(QWidget *parent = 0);
    ~mod_main();
private:
//    void init();
    void init_conn();
    void set_button_enabled();
private:
    void file_operations(const QString& s);
    void file_new ();
    void file_open ();
    void file_save();
    void file_save_as();
private:
    void copy();
    void cut();
    void paste();
    void del();
    void add_row();
    void on_measure_date ();
    void on_measure_man ();
    void on_task_man ();
    void help_advice();
private:
    not_null<mod_analysis*> create_window (const QString & title);
    mod_analysis* active_window();
private:
    Ui::mod_main *ui;
};

#endif // MOD_MAIN_H
