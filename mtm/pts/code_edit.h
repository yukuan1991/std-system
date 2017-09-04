#ifndef CODE_EDIT_H
#define CODE_EDIT_H
#include <QLineEdit>
#include <utility>
#include <QDebug>


class code_edit : public QLineEdit
{
public:
    code_edit(auto&& ... args) : QLineEdit (std::forward<decltype(args)> (args)...)
    {
        qDebug () << "created";
    }
protected:
    void focusInEvent(QFocusEvent *e) override
    {
        QLineEdit::focusInEvent (e);
        deselect ();
        qDebug () << "focus in event";
    }
    ~code_edit () override = default;
};

#endif // CODE_EDIT_H
