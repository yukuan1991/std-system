#include <QListWidget>

class PwhListWidget : public QListWidget
{
public:
    PwhListWidget(QWidget* parent = nullptr);
    void insert (const QString& fileName, const QVariant & data, int index);
    void append (const QString& fileName, const QVariant & data) { insert (fileName, data, count ()); }

    void up();
    void down();
private:
    void close();
};

