#include <QApplication>
#include <QHeaderView>
#include <QTableWidget>
#include <QStringList>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QTableWidget table(1000000, 3);
    table.setWindowTitle("Basic QTableWidget Example");
    table.setHorizontalHeaderLabels(QStringList{"Name", "Age", "City"});
    table.verticalHeader()->setVisible(false);
    table.horizontalHeader()->setStretchLastSection(true);

    for (size_t i = 0; i < 1000000; i++)
    {
        table.setItem(i, 0, new QTableWidgetItem("Alex"));
        table.setItem(i, 1, new QTableWidgetItem(QString::number(i)));
        table.setItem(i, 2, new QTableWidgetItem("Kyiv"));
    }
    


    // table.setItem(1, 0, new QTableWidgetItem("Marta"));
    // table.setItem(1, 1, new QTableWidgetItem("25"));
    // table.setItem(1, 2, new QTableWidgetItem("Lviv"));

    // table.setItem(2, 0, new QTableWidgetItem("Dmytro"));
    // table.setItem(2, 1, new QTableWidgetItem("30"));
    // table.setItem(2, 2, new QTableWidgetItem("Odesa"));

    // table.setItem(3, 0, new QTableWidgetItem("Iryna"));
    // table.setItem(3, 1, new QTableWidgetItem("28"));
    // table.setItem(3, 2, new QTableWidgetItem("Kharkiv"));

    table.resize(500, 240);
    table.show();

    return app.exec();
}
