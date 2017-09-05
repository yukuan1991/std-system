#ifndef MOST_MAIN_H
#define MOST_MAIN_H

#include <QWidget>
#include "most_analysis.h"
#include <base/lang/not_null.h>

namespace Ui {
class most_main;
}

class most_main : public QWidget
{
    Q_OBJECT

public:
    explicit most_main(QWidget *parent = 0);
    ~most_main();

private:
    void init_conn();
    void set_button_enabled();

private:
    void file_operations(const QString& s);
    void file_new();
    void file_open();
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
    not_null<most_analysis*> create_window (const QString & title);
    most_analysis* active_window();
private:
    Ui::most_main *ui;
};

#endif // MOST_MAIN_H
