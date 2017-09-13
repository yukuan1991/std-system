#ifndef PWHMANAGEMENTRIBBON_H
#define PWHMANAGEMENTRIBBON_H
#include "utils/ribbon.h"

class PwhManagementRibbon : public ribbon
{
    Q_OBJECT
signals:
    void addClicked();
    void modifyClicked();
    void deleteClicked();

    void addStdDatabaseClicked();
    void detailedInfoClicked();
    void exportPDFClicked();
    void reportHeaderClicked();
public:
    PwhManagementRibbon(QWidget* parent = nullptr);
    ribbon_tool* add_, *modify_, * delete_;
    ribbon_tool* addStdDatabase_;
    ribbon_tool* detailedInfo_;
    ribbon_tool* exportPDF_;
    ribbon_tool* reportHeader_;
private:
    void initConn();
};

#endif // PWHMANAGEMENTRIBBON_H
