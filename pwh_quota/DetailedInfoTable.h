#ifndef DETAILEDINFOTABLE_H
#define DETAILEDINFOTABLE_H

#include <QTableWidget>

class DetailedInfoTable : public QTableWidget
{
public:
    DetailedInfoTable(QWidget *parent = nullptr);
    void load(const QString& method, const QVariant& data);
private:
    void loadVaf(const QVariant& data);
    void loadPts(const QVariant& data);
    void loadStd(const QVariant& data);
};

#endif // DETAILEDINFOTABLE_H
