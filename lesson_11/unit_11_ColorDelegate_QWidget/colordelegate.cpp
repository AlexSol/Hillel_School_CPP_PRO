#include "colordelegate.h"
#include <QColorDialog>
#include <QPainter>

ColorDelegate::ColorDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Отримуємо колір з моделі
    QColor color = index.data(Qt::DisplayRole).value<QColor>();

    // Малюємо прямокутник із заповненням кольором
    painter->save();
    painter->setBrush(color);
    painter->drawRect(option.rect);
    painter->restore();
}

QWidget *ColorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
    // Використовуємо QColorDialog як редактор
    return new QColorDialog(parent);
}

void ColorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // Отримуємо колір з моделі і встановлюємо його в QColorDialog
    QColor color = index.data(Qt::DisplayRole).value<QColor>();
    QColorDialog *colorDialog = qobject_cast<QColorDialog*>(editor);
    colorDialog->setCurrentColor(color);
}

void ColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    // Отримуємо вибраний колір з QColorDialog і встановлюємо його в модель
    QColorDialog *colorDialog = qobject_cast<QColorDialog*>(editor);
    model->setData(index, colorDialog->currentColor(), Qt::DisplayRole);
}
