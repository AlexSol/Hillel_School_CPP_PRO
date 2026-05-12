#include "TaskModel.h"

TaskModel::TaskModel(QObject *parent)
    : QAbstractListModel(parent)
{
    addTask(QStringLiteral("Prepare lesson notes"), 2);
    addTask(QStringLiteral("Create QML demo"), 3);
    addTask(QStringLiteral("Review pull request"), 1);
}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_tasks.size();
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_tasks.size()) {
        return {};
    }

    const Task &task = m_tasks.at(index.row());

    switch (role) {
    case TitleRole:
        return task.title;
    case DoneRole:
        return task.done;
    case PriorityRole:
        return task.priority;
    default:
        return {};
    }
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    return {
        {TitleRole, "title"},
        {DoneRole, "done"},
        {PriorityRole, "priority"}
    };
}

bool TaskModel::addTask(const QString &title, int priority)
{
    const QString trimmedTitle = title.trimmed();
    if (trimmedTitle.isEmpty()) {
        return false;
    }

    const int boundedPriority = qBound(1, priority, 3);

    const int nextRow = m_tasks.size();
    beginInsertRows(QModelIndex(), nextRow, nextRow);
    m_tasks.push_back(Task{trimmedTitle, false, boundedPriority});
    endInsertRows();
    return true;
}

bool TaskModel::toggleTask(int index)
{
    if (index < 0 || index >= m_tasks.size()) {
        return false;
    }

    Task &task = m_tasks[index];
    task.done = !task.done;

    const QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, {DoneRole});
    return true;
}

int TaskModel::removeCompleted()
{
    int removed = 0;

    for (int i = m_tasks.size() - 1; i >= 0; --i) {
        if (!m_tasks[i].done) {
            continue;
        }

        beginRemoveRows(QModelIndex(), i, i);
        m_tasks.removeAt(i);
        endRemoveRows();
        ++removed;
    }

    return removed;
}

int TaskModel::completedCount() const
{
    int done = 0;
    for (const Task &task : m_tasks) {
        if (task.done) {
            ++done;
        }
    }
    return done;
}
