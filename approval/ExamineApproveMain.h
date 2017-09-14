#ifndef EXAMINEAPPROVEMAIN_H
#define EXAMINEAPPROVEMAIN_H

#include <QWidget>

namespace Ui {
class ExamineApproveMain;
}

class QTableWidget;

class ExamineApproveMain : public QWidget
{
    Q_OBJECT
signals:
    void selectedData(const QVariant& id);
    void agree(const QVariant& id);
    void disagree(const QVariant& id);
public:
    explicit ExamineApproveMain(QWidget *parent = 0);
    ~ExamineApproveMain();

    void loadExamineApproveTable(const QVariant& data);
    void loadRelatedInfoTable(const QVariant& data);
private:
    void onCellClicked(int row);
    void onButtonAgreeClicked();
    void onButtonDisagreeClicked();
    int findHeaderCol(const QStringList&, const QString&);
    void setTableData(QTableWidget* table, int row, int col, const QVariant& data);
private:
    Ui::ExamineApproveMain *ui;
};

#endif // EXAMINEAPPROVEMAIN_H
