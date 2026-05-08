#include <QApplication>
#include <QHeaderView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTableView>

#include <chrono>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto start = std::chrono::high_resolution_clock::now();

    QStandardItemModel* model = new QStandardItemModel(100000, 3);
    model->setHorizontalHeaderLabels(QStringList{"Col 1", "Col 2", "Col 3"});

    for (int i = 0; i < 100000; ++i) {
        for (int j = 0; j < 3; ++j) {
            model->setItem(i, j, new QStandardItem("Data"));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "QStandardItemModel time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    QTableView* view = new QTableView();
    view->setModel(model);
    view->setWindowTitle("QTableView + QStandardItemModel");
    view->horizontalHeader()->setStretchLastSection(true);
    view->resize(700, 420);
    view->show();

    return app.exec();
}
