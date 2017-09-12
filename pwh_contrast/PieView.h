#pragma once

#include <QWidget>
#include <QChartView>
#include <memory>

namespace QtCharts {
class QChartView;
}

class PieView : public QtCharts::QChartView
{
    Q_OBJECT
signals:
    void hoveredItem (const QString &);
public:
    explicit PieView (QWidget *parent = 0);
    ~PieView () override;
    void setTitle (const QString & title);
    void setSlices (const QVariantList & list);
private:
    void setChart (std::unique_ptr<QtCharts::QChart> chart);
};

