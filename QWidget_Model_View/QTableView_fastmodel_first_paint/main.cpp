#include <QAbstractTableModel>
#include <QApplication>
#include <QEvent>
#include <QTableView>

#include <chrono>
#include <iostream>

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

class FirstPaintTimer : public QObject {
public:
    explicit FirstPaintTimer(std::chrono::high_resolution_clock::time_point start)
        : start_(start) {}

protected:
    bool eventFilter(QObject* watched, QEvent* event) override {
        if (!printed_ && event->type() == QEvent::Paint) {
            const auto end = std::chrono::high_resolution_clock::now();
            std::cout << "First paint time: "
                      << std::chrono::duration_cast<std::chrono::milliseconds>(end - start_).count()
                      << " ms\n";
            printed_ = true;
            watched->removeEventFilter(this);
            deleteLater();
        }
        return QObject::eventFilter(watched, event);
    }

private:
    std::chrono::high_resolution_clock::time_point start_;
    bool printed_ = false;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    auto start = std::chrono::high_resolution_clock::now();

    auto* model = new FastModel();

    QTableView view;
    view.setModel(model);
    view.setWindowTitle("FastModel first paint timing");
    view.resize(900, 520);

    auto* timer = new FirstPaintTimer(start);
    view.viewport()->installEventFilter(timer);

    view.show();

    return app.exec();
}
