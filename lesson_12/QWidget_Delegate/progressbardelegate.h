#ifndef PROGRESSBARDELEGATE_H
#define PROGRESSBARDELEGATE_H

#include <QProgressBar>
#include <QApplication>
#include <QStyledItemDelegate>

class ProgressBarDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit ProgressBarDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        int progress = index.data(Qt::DisplayRole).toInt();

        QStyleOptionProgressBar progressBarOption;
        progressBarOption.rect = option.rect;
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.progress = progress;
        progressBarOption.text = QString("%1%").arg(progress);
        progressBarOption.textVisible = true;

        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    }
};

#endif // PROGRESSBARDELEGATE_H
