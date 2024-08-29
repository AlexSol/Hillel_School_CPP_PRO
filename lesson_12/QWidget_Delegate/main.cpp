#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QTimer>
#include "colordelegate.h"
#include "progressbardelegate.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Создаём модель данных
    QStandardItemModel model(5, 3); // 5 строк, 3 столбца

    // Заполняем модель данными
    for (int row = 0; row < 5; ++row) {
        QModelIndex levelIndex = model.index(row, 0);
        int level = 20 + row * 15;  // Пример значений уровня заполнения
        model.setData(levelIndex, level);

        QModelIndex colorIndex = model.index(row, 1);
        QColor color = QColor::fromHsv(row * 60, 255, 200);
        QString substance = QString("Substance %1").arg(row + 1);
        model.setData(colorIndex, substance, Qt::DisplayRole);
        model.setData(colorIndex, color, Qt::DecorationRole);

        QModelIndex progressIndex = model.index(row, 2);
        model.setData(progressIndex, level);

        // Делаем третью колонку только для чтения
        QStandardItem *item = model.itemFromIndex(progressIndex);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    }

    // Создаём таблицу
    QTableView tableView;

    // // Создаём делегаты
    ColorDelegate *colorDelegate = new ColorDelegate(&tableView);
    ProgressBarDelegate *progressBarDelegate = new ProgressBarDelegate(&tableView);

    // // Назначаем делегаты для соответствующих колонок
    // tableView.setItemDelegateForColumn(1, colorDelegate);
    tableView.setItemDelegateForColumn(2, progressBarDelegate);

    tableView.setModel(&model);
    tableView.show();


    // Создаём таймер для изменения данных
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        for (int row = 0; row < 5; ++row) {
            QModelIndex levelIndex = model.index(row, 0);
            int level = (model.data(levelIndex).toInt() + 10) % 100; // Обновляем уровень заполнения
            model.setData(levelIndex, level);

            QModelIndex progressIndex = model.index(row, 2);
            model.setData(progressIndex, level); // Обновляем прогресс-бар

            // Уведомляем таблицу об изменении данных в строке
            model.dataChanged(levelIndex, progressIndex);
        }
    });

    timer.start(1000); // Обновляем данные каждые 1 секунду

    return app.exec();
}
