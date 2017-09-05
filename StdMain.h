#ifndef STDMAIN_H
#define STDMAIN_H

#include <QWidget>

namespace Ui {
class StdMain;
}

class StdMain : public QWidget
{
    Q_OBJECT
public:
    explicit StdMain(QWidget *parent = 0);
    ~StdMain();
private:
    Ui::StdMain *ui;
};

#endif // STDMAIN_H
