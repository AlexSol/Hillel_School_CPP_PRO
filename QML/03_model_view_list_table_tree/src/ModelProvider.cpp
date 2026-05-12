#include "ModelProvider.h"

#include <QStandardItem>

ModelProvider::ModelProvider(QObject *parent)
    : QObject(parent)
{
    initListModel();
    initTableModel();
    initTreeModel();
}

QAbstractItemModel *ModelProvider::listModel()
{
    return &m_listModel;
}

QAbstractItemModel *ModelProvider::tableModel()
{
    return &m_tableModel;
}

QAbstractItemModel *ModelProvider::treeModel()
{
    return &m_treeModel;
}

void ModelProvider::initListModel()
{
    m_listModel.setStringList({
        "Qt", "QML", "Qt Quick", "Model/View", "Signals", "Slots", "Delegates"
    });
}

void ModelProvider::initTableModel()
{
    m_tableModel.setColumnCount(3);
    m_tableModel.setHorizontalHeaderLabels({"Student", "Score", "Level"});

    const QList<QList<QVariant>> rows = {
        {"Alex", 95, "A"},
        {"Ira", 88, "B+"},
        {"Maks", 76, "C"},
        {"Nina", 91, "A-"}
    };

    for (const auto &rowData : rows) {
        QList<QStandardItem*> items;
        for (const auto &value : rowData) {
            items.push_back(new QStandardItem(value.toString()));
        }
        m_tableModel.appendRow(items);
    }
}

void ModelProvider::initTreeModel()
{
    m_treeModel.setHorizontalHeaderLabels({"Topic"});

    auto *cppItem = new QStandardItem("C++");
    cppItem->appendRow(new QStandardItem("Pointers"));
    cppItem->appendRow(new QStandardItem("Smart pointers"));

    auto *qtItem = new QStandardItem("Qt");
    qtItem->appendRow(new QStandardItem("QObject"));
    qtItem->appendRow(new QStandardItem("Signals/Slots"));

    auto *qmlItem = new QStandardItem("QML");
    qmlItem->appendRow(new QStandardItem("ListView"));
    qmlItem->appendRow(new QStandardItem("TableView"));
    qmlItem->appendRow(new QStandardItem("TreeView"));

    m_treeModel.appendRow(cppItem);
    m_treeModel.appendRow(qtItem);
    m_treeModel.appendRow(qmlItem);
}
