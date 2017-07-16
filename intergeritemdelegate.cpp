#include "intergeritemdelegate.h"
#include <QSpinBox>

IntergerItemDelegate::IntergerItemDelegate(QObject *parent):
    QItemDelegate(parent)
{}

QWidget *IntergerItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    auto spinner = new QSpinBox(parent);
    spinner->setMinimum(0);
    spinner->setMaximum(20);
    spinner->setSingleStep(1);
    return spinner;
}

void IntergerItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto spinner = static_cast<QSpinBox*>(editor);
    spinner->setValue(index.data().toInt());
}

void IntergerItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto spinner = static_cast<QSpinBox*>(editor);
    model->setData(index, spinner->value());
}

void IntergerItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
