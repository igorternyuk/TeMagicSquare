#ifndef ITERGERITEMDELEGATE_H
#define ITERGERITEMDELEGATE_H

#include <QItemDelegate>

class IntergerItemDelegate : public QItemDelegate
{

public:

    IntergerItemDelegate(QObject *parent = nullptr);

protected:

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const override;

};

#endif // ITERGERITEMDELEGATE_H
