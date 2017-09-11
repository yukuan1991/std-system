#pragma once

#include <QWidget>
#include <base/lang/not_null.h>

namespace Ui {
class StatView;
}

class PieView;
class QTableWidgetItem;

class StatView : public QWidget
{
    Q_OBJECT
signals:
    void closeView ();
public:
    explicit StatView(QWidget *parent = 0);
    ~StatView();
    not_null<PieView*> pie () const;
    bool load (const QVariantMap & data);
    QVariant dump () const;
    void setFileTitle(const QString & title);
private:
    void initTable ();
    void onPieHovered (const QString & name);
    QTableWidgetItem* cell (const QString & horizontalHeader, const QString & verticalHeader) const;
private:
    Ui::StatView *ui;
};

