#ifndef COLORDELEGATE_H
#define COLORDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>

class ColorDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit ColorDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QString text = index.data(Qt::DisplayRole).toString();
        QColor color = index.data(Qt::DecorationRole).value<QColor>();

        painter->save();

        // Рисуем цвет
        QRect rect = option.rect;
        rect.setWidth(20);
        painter->fillRect(rect, color);

        // Рисуем текст
        painter->drawText(option.rect.adjusted(25, 0, 0, 0), Qt::AlignVCenter, text);

        painter->restore();
    }
};
#endif // COLORDELEGATE_H
