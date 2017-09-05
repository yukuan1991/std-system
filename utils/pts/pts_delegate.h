#ifndef PTS_DELEGATE_LEFT_H
#define PTS_DELEGATE_LEFT_H
#include <QStyledItemDelegate>
#include <map>
#include <string>


class pts_delegate : public QStyledItemDelegate
{
public:
    pts_delegate(QObject* parent = nullptr);

    QWidget *createEditor (QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData (QWidget* editor, const QModelIndex& index) const override;
    void setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry (QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    compl pts_delegate () override = default;

private:
    void set_code (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
private:
    std::map<std::string, int> kv_tmu_;
};

#endif // PTS_DELEGATE_LEFT_H
