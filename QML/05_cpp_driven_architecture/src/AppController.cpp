#include "AppController.h"

AppController::AppController(QObject *parent)
    : QObject(parent)
{
    auto notify = [this]() { emit summaryChanged(); };

    connect(&m_taskModel, &QAbstractItemModel::rowsInserted, this, notify);
    connect(&m_taskModel, &QAbstractItemModel::rowsRemoved, this, notify);
    connect(&m_taskModel, &QAbstractItemModel::dataChanged, this, notify);
    connect(&m_taskModel, &QAbstractItemModel::modelReset, this, notify);
}

TaskModel *AppController::taskModel()
{
    return &m_taskModel;
}

QString AppController::summary() const
{
    const int total = m_taskModel.rowCount();
    const int done = m_taskModel.completedCount();
    return QStringLiteral("Completed %1 of %2 tasks").arg(done).arg(total);
}

bool AppController::addTask(const QString &title, int priority)
{
    const bool ok = m_taskModel.addTask(title, priority);
    if (ok) {
        emit summaryChanged();
    }
    return ok;
}

bool AppController::toggleTask(int index)
{
    const bool ok = m_taskModel.toggleTask(index);
    if (ok) {
        emit summaryChanged();
    }
    return ok;
}

int AppController::removeCompleted()
{
    const int removed = m_taskModel.removeCompleted();
    if (removed > 0) {
        emit summaryChanged();
    }
    return removed;
}
