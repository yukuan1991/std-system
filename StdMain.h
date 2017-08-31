#ifndef STDMAIN_H
#define STDMAIN_H

#include <QWidget>

namespace Ui {
class StdMain;
}

class StdMain : public QWidget
{
    Q_OBJECT
//signals:
    //void posDragged (QPoint);
public:
    explicit StdMain(QWidget *parent = 0);
    ~StdMain();
private slots:
    void onPosChanged (int x, int y);
    void onstackChanged(QString name);
private:
    Ui::StdMain *ui;
};

#endif // STDMAIN_H
