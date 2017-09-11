#include <QListWidget>

class PwhListWidget : public QListWidget
{
public:
    PwhListWidget(QWidget* parent = nullptr);
    void insert (const QVariant & data, int index);
    void append (const QVariant & data) { insert (data, count ()); }

    void up();
    void down();
private:
    void close();
};

