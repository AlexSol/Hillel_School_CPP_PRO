#include <QApplication>
#include <QGroupBox>
#include <QHeaderView>
#include <QListView>
#include <QMainWindow>
#include <QSplitter>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTableView>
#include <QTreeView>
#include <QVBoxLayout>

#include "regiondelegate.h"
#include "sensormodel.h"
#include "temperaturedelegate.h"

static QStandardItemModel* buildAreaTreeModel(QObject* parent)
{
    auto* model = new QStandardItemModel(0, 1, parent);
    model->setHorizontalHeaderLabels({"Area / City"});

    struct Area { QString name; QStringList cities; };
    const QList<Area> areas = {
        {"Central Ukraine",  {"Kyiv", "Cherkasy", "Kremenchuk"}},
        {"Western Ukraine",  {"Lviv", "Ivano-Frankivsk", "Uzhhorod", "Ternopil"}},
        {"Southern Ukraine", {"Odesa", "Mykolaiv", "Kherson"}},
        {"Eastern Ukraine",  {"Kharkiv", "Zaporizhzhia", "Dnipro"}},
    };

    for (const auto& area : areas) {
        auto* areaItem = new QStandardItem(area.name);
        areaItem->setEditable(false);
        QFont f = areaItem->font();
        f.setBold(true);
        areaItem->setFont(f);
        areaItem->setForeground(QColor(50, 100, 200));

        for (const auto& city : area.cities) {
            auto* cityItem = new QStandardItem("  " + city);
            cityItem->setEditable(false);
            areaItem->appendRow(cityItem);
        }
        model->appendRow(areaItem);
    }
    return model;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("Model / View + Delegates Demo");
    window.resize(1150, 720);

    auto* central    = new QWidget();
    auto* mainLayout = new QVBoxLayout(central);
    mainLayout->setSpacing(6);

    // ── QTableView: temperature sensors ─────────────────────────────────────
    auto* sensorGroup  = new QGroupBox("Temperature Sensors  (live simulation, updates every 1 s)");
    auto* sensorLayout = new QVBoxLayout(sensorGroup);

    auto* sensorModel = new SensorModel(&window);
    auto* tableView   = new QTableView();
    tableView->setModel(sensorModel);
    tableView->setItemDelegateForColumn(2, new TemperatureDelegate(tableView));
    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    tableView->setColumnWidth(0, 50);
    tableView->setColumnWidth(2, 110);
    tableView->setColumnWidth(3, 90);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setAlternatingRowColors(true);
    tableView->verticalHeader()->setVisible(false);
    tableView->setMinimumHeight(220);
    sensorLayout->addWidget(tableView);
    mainLayout->addWidget(sensorGroup);

    // ── Bottom: QListView + QTreeView ────────────────────────────────────────
    auto* bottomSplitter = new QSplitter(Qt::Horizontal);

    // QListView — regions
    auto* listGroup  = new QGroupBox("Regions");
    auto* listLayout = new QVBoxLayout(listGroup);
    auto* regionModel = new QStringListModel(
        QStringList{
            "Kyiv region",        "Lviv region",
            "Odesa region",       "Kharkiv region",
            "Dnipro region",      "Zaporizhzhia region",
            "Mykolaiv region",    "Ternopil region",
        },
        &window);
    auto* listView = new QListView();
    listView->setModel(regionModel);
    listView->setItemDelegate(new RegionDelegate(listView));
    listLayout->addWidget(listView);
    bottomSplitter->addWidget(listGroup);

    // QTreeView — areas with nested cities
    auto* treeGroup  = new QGroupBox("Areas and Cities");
    auto* treeLayout = new QVBoxLayout(treeGroup);
    auto* treeModel  = buildAreaTreeModel(&window);
    auto* treeView   = new QTreeView();
    treeView->setModel(treeModel);
    treeView->expandAll();
    treeView->header()->setStretchLastSection(true);
    treeLayout->addWidget(treeView);
    bottomSplitter->addWidget(treeGroup);

    bottomSplitter->setSizes({350, 450});
    mainLayout->addWidget(bottomSplitter);

    window.setCentralWidget(central);
    window.show();

    return app.exec();
}
