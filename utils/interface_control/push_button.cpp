#include "push_button.h"

void push_button::init()
{
    this->setMouseTracking (true);
}

void push_button::enterEvent(QEvent *)
{
    emit mouse_enter ();
}

void push_button::leaveEvent (QEvent *)
{
    emit signal_mouse_leave ();
}
