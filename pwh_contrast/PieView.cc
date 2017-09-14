#include "PieView.h"
#include <QChart>
#include <QPieSeries>
#include <QPieSeries>
#include <base/lang/scope.hpp>
#include <assert.h>

using namespace QtCharts;

PieView::PieView(QWidget *parent)
    :QChartView (parent)
{
    setChart (std::make_unique<QChart> ());
    setRenderHint (QPainter::Antialiasing);

    auto series = std::make_unique<QPieSeries> ();
    chart ()->addSeries (series.get ());
    SCOPE_EXIT { series.release (); };

    chart ()->setAnimationOptions (QChart::AllAnimations);

    series->setHorizontalPosition (0.5);
    series->setVerticalPosition(0.6);
    series->setPieSize (0.7);
}

PieView::~PieView()
{

}

void PieView::setChart(std::unique_ptr<QChart> chart)
{
    std::unique_ptr<QChart> oldChart (static_cast<QChartView*> (this)->chart ());
    static_cast<QChartView*> (this)->setChart (chart.release ());
}

void PieView::setSlices(const QVariantList &list)
{
    auto series = chart ()->series (); assert (series.size () == 1);
    auto pie = dynamic_cast<QPieSeries *> (series.at (0)); assert (pie);

    pie->clear ();

    for (auto & var : list)
    {
        auto map = var.toMap ();
        const auto percent = map ["percent"].toDouble ();
        const auto name = map ["name"].toString ();

        const auto color = map ["color"].value<QColor> ();

        auto slice = std::make_unique<QPieSlice> (pie);
        slice->setValue (percent);
        slice->setLabel (name);

        if (color.isValid ())
        {
            slice->setBrush (color);
        }

        connect (slice.get (), &QPieSlice::hovered, [this, slice = slice.get ()] (bool b)
        {
            this->hoveredItem (b ? slice->label () : QString ());
        });
        slice->setExplodeDistanceFactor (0.04);

        connect (slice.get (), &QPieSlice::hovered, slice.get (), &QPieSlice::setExploded);
        connect (slice.get (), &QPieSlice::hovered, slice.get (), &QPieSlice::setLabelVisible);

        pie->append (slice.release ());
    }
}

void PieView::setTitle(const QString &title)
{
    chart ()->setTitle (title);
}
