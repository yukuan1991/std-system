#ifndef STDMAIN_H
#define STDMAIN_H

#include <QWidget>
#include<memory>

namespace Ui {
class StdMain;
}
class IoManipulator;

class StdMain : public QWidget
{
    Q_OBJECT
public:
    explicit StdMain (QWidget *parent = 0);
    void setIoManipulator (std::shared_ptr<IoManipulator> p);
    ~StdMain();
private:
    Ui::StdMain *ui;
};

#endif // STDMAIN_H
