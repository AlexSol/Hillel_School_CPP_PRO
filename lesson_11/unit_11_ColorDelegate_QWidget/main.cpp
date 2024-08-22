#include "mainwindow.h"
#include <QApplication>

#include <QListView>
#include <QStandardItemModel>
#include "colordelegate.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Створюємо модель з кольорами
    QStandardItemModel model(5, 1);
    for (int row = 0; row < 5; ++row) {
        QModelIndex index = model.index(row, 0);
        model.setData(index, QColor(Qt::red).lighter(100 + row * 20));
    }

    // Створюємо QListView і встановлюємо модель
    QListView listView;
    listView.setModel(&model);

    // Встановлюємо власний делегат для списку
    ColorDelegate *delegate = new ColorDelegate(&listView);
    listView.setItemDelegate(delegate);

    listView.show();

    return app.exec();
}
