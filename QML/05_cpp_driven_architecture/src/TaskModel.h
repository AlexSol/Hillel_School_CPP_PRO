#pragma once

#include <QAbstractListModel>

class TaskModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        TitleRole = Qt::UserRole + 1,
        DoneRole,
        PriorityRole
    };
    Q_ENUM(Roles)

    explicit TaskModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool addTask(const QString &title, int priority);
    bool toggleTask(int index);
    int removeCompleted();

    int completedCount() const;

private:
    struct Task {
        QString title;
        bool done = false;
        int priority = 1;
    };

    QList<Task> m_tasks;
};
