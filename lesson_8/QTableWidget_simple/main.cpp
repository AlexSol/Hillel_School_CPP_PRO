#include <QApplication>
#include <QTableWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QTableWidget table(3, 3);
    table.setWindowTitle("QTableWidget Example");

    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            table.setItem(row, column, new QTableWidgetItem(QString("Item %1").arg(row * 3 + column + 1)));
        }
    }

    table.show();

    return app.exec();
}
