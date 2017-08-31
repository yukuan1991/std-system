#ifndef VIDEO2_H
#define VIDEO2_H

#include <QWidget>

namespace Ui {
class video2;
}

class video2 : public QWidget
{
    Q_OBJECT

public:
    explicit video2(QWidget *parent = 0);
    ~video2();

private:
    Ui::video2 *ui;
};

#endif // VIDEO2_H
