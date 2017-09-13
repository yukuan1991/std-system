#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class ReportTableWidget;
}

class ReportTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportTableWidget(QWidget *parent = 0);
    ~ReportTableWidget();

    QVariant dump();
    void load(const QVariant& data);

    void setReportHeader(const QString& title);
    QString reportHeader() const;

private:
    Ui::ReportTableWidget *ui;
};

#endif // WIDGET_H
