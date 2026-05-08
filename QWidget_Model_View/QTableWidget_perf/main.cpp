#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <chrono>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto start = std::chrono::high_resolution_clock::now();

    QTableWidget* table = new QTableWidget(100000, 3);

    for(int i = 0; i < 100000; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            table->setItem(i, j, new QTableWidgetItem("Data"));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "QTableWidget time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    table->setWindowTitle("QTableWidget Perf");
    table->show();

    return app.exec();
}
