#include <QAbstractTableModel>
#include <QApplication>
#include <QTableView>

class FastModel : public QAbstractTableModel {
public:
    int rowCount(const QModelIndex&) const override { return 1'000'000; }
    int columnCount(const QModelIndex&) const override { return 3; }

    QVariant data(const QModelIndex& index, int role) const override {
        if (role == Qt::DisplayRole) {
            return QString("Row %1 Col %2")
                .arg(index.row())
                .arg(index.column());
        }
        return {};
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    auto* model = new FastModel();

    QTableView view;
    view.setModel(model);
    view.setWindowTitle("QTableView + FastModel (QAbstractTableModel)");
    view.resize(900, 520);
    view.show();

    return app.exec();
}
