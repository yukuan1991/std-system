#ifndef VIDEOTRIALRIBBON_H
#define VIDEOTRIALRIBBON_H

#include "utils/ribbon.h"

class VideoTrialRibbon : public ribbon
{
    Q_OBJECT
signals:
    void cut ();
    void copy ();
    void del ();
    void paste ();

    void change_task_count ();

    void import_data ();
    void invalid_timespan ();

    void measure_date ();
    void measure_man ();
    void task_man ();

    void export_data ();
public:
    VideoTrialRibbon(QWidget *parent = nullptr);
private:
    ribbon_tool *cut_, *copy_, *paste_, *del_;
    ribbon_tool *add_row_;
    ribbon_tool *export_;
    ribbon_tool *import_, *inactive_time_;
    ribbon_tool *measure_date_, *measure_man_, *task_man_;
};

#endif // VIDEOTRIALRIBBON_H
