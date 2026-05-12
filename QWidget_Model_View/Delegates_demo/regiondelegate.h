#pragma once

#include <QPainter>
#include <QStyledItemDelegate>

// Delegate for QListView of regions.
// Renders a colored circle bullet before the region name.
class RegionDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit RegionDelegate(QObject* parent = nullptr)
        : QStyledItemDelegate(parent) {}

    void paint(QPainter*                   painter,
               const QStyleOptionViewItem& option,
               const QModelIndex&          index) const override
    {
        painter->save();

        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());

        static const QColor palette[] = {
            {220,  80,  80}, { 80, 160, 220}, { 80, 200, 120},
            {200, 160,  60}, {160,  80, 200}, { 80, 200, 200},
            {220, 130,  60}, {100, 100, 200},
        };
        const QColor dot = palette[index.row() % 8];

        const int cx = option.rect.left() + 14;
        const int cy = option.rect.top()  + option.rect.height() / 2;
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(dot);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(QPoint(cx, cy), 6, 6);

        QRect textRect = option.rect.adjusted(30, 0, -4, 0);
        painter->setPen((option.state & QStyle::State_Selected)
                            ? option.palette.highlightedText().color()
                            : option.palette.text().color());
        painter->drawText(textRect, Qt::AlignVCenter,
                          index.data(Qt::DisplayRole).toString());

        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem& option,
                   const QModelIndex&          index) const override
    {
        auto sz = QStyledItemDelegate::sizeHint(option, index);
        sz.setHeight(30);
        return sz;
    }
};
