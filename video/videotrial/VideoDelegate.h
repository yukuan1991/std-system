#ifndef VIDEODELEGATE_H
#define VIDEODELEGATE_H

#include <QStyledItemDelegate>
#include "video/videotrial/VideoFormModel.h"


class VideoDelegate : public QStyledItemDelegate
{
public:
    VideoDelegate(QObject* parent = nullptr);

    QWidget *createEditor (QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData (QWidget* editor, const QModelIndex& index) const override;
    void setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry (QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    ~VideoDelegate () override = default;

private:
    QWidget* create_result_editor (QWidget* parent, const QModelIndex& index, VideoFormModel* src_model) const;
    void set_result_editor (QWidget* editor, const QModelIndex& index, VideoFormModel* src_model) const;
    void set_result_model (QWidget* editor, VideoFormModel* src_model, const QModelIndex& index) const;
};

#endif // VIDEODELEGATE_H
