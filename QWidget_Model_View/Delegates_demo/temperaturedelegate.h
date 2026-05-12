#pragma once

#include <QPainter>
#include <QStyledItemDelegate>

// Delegates for the Temperature column in QTableView.
// Paints the cell background based on the temperature value:
//   < 15 °C  -> blue   (cold)
//   15-30 °C -> green  (normal)
//   30-40 °C -> orange (warning)
//   > 40 °C  -> red    (critical)
class TemperatureDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit TemperatureDelegate(QObject* parent = nullptr)
        : QStyledItemDelegate(parent) {}

    void paint(QPainter*                   painter,
               const QStyleOptionViewItem& option,
               const QModelIndex&          index) const override
    {
        bool   ok;
        double temp = index.data(Qt::DisplayRole)
                          .toString()
                          .replace("\xc2\xb0""C", "") // °C
                          .trimmed()
                          .toDouble(&ok);

        QColor bg = Qt::white;
        if (ok) {
            if      (temp < 15.0) bg = QColor(100, 180, 255);
            else if (temp < 30.0) bg = QColor(120, 220, 120);
            else if (temp < 40.0) bg = QColor(255, 200,  80);
            else                  bg = QColor(255,  80,  80);
        }

        painter->save();
        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());
        else
            painter->fillRect(option.rect, bg);

        painter->setPen((option.state & QStyle::State_Selected)
                            ? option.palette.highlightedText().color()
                            : Qt::black);
        painter->drawText(option.rect.adjusted(4, 0, -4, 0),
                          Qt::AlignVCenter | Qt::AlignHCenter,
                          index.data(Qt::DisplayRole).toString());
        painter->restore();
    }
};
