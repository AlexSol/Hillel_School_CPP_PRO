#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QStandardItemModel model(4, 3);
    QTableView tableView;
    tableView.setModel(&model);
    tableView.show();

    return app.exec();
}
