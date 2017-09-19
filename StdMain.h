#ifndef STDMAIN_H
#define STDMAIN_H

#include <QWidget>
#include<memory>
#include <QTabBar>
#include <QTabWidget>

namespace Ui {
class StdMain;
}
class IoManipulator;

class MainTabBar : public QTabBar
{
    Q_OBJECT
public:
    MainTabBar (QWidget * parent = nullptr) : QTabBar (parent) {}
};

class MainTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    MainTabWidget(QWidget *parent = Q_NULLPTR) : QTabWidget (parent) { this->setTabBar(new MainTabBar(this)); }
};

class StdMain : public QWidget
{
    Q_OBJECT
public:
    explicit StdMain (QWidget *parent = 0);
    void setIoManipulator (std::shared_ptr<IoManipulator> p);
    ~StdMain();
private:
    void onTabClicked(int index);
    void setTabBar(QTabBar*);
private:
    Ui::StdMain *ui;
};

#endif // STDMAIN_H
