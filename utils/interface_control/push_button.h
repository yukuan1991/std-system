#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <QObject>
#include <QPushButton>
#include <QWidget>

class push_button : public QPushButton
{
    Q_OBJECT
public:
    template<typename ... ARGS>
    push_button (ARGS&& ... args): QPushButton (std::forward<ARGS>(args)...)
    {

    }

    void init ();

protected:
    virtual void enterEvent (QEvent *);
    virtual void leaveEvent (QEvent *);
signals:
    void mouse_enter ();
    void signal_mouse_leave ();
};

#endif // PUSH_BUTTON_H
