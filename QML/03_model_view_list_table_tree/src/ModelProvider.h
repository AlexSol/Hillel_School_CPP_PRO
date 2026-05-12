#pragma once

#include <QObject>
#include <QStringListModel>
#include <QStandardItemModel>

class ModelProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel* listModel READ listModel CONSTANT)
    Q_PROPERTY(QAbstractItemModel* tableModel READ tableModel CONSTANT)
    Q_PROPERTY(QAbstractItemModel* treeModel READ treeModel CONSTANT)

public:
    explicit ModelProvider(QObject *parent = nullptr);

    QAbstractItemModel* listModel();
    QAbstractItemModel* tableModel();
    QAbstractItemModel* treeModel();

private:
    void initListModel();
    void initTableModel();
    void initTreeModel();

    QStringListModel m_listModel;
    QStandardItemModel m_tableModel;
    QStandardItemModel m_treeModel;
};
