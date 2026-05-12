#pragma once

#include <QObject>

#include "TaskModel.h"

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TaskModel* taskModel READ taskModel CONSTANT)
    Q_PROPERTY(QString summary READ summary NOTIFY summaryChanged)

public:
    explicit AppController(QObject *parent = nullptr);

    TaskModel* taskModel();
    QString summary() const;

    Q_INVOKABLE bool addTask(const QString &title, int priority);
    Q_INVOKABLE bool toggleTask(int index);
    Q_INVOKABLE int removeCompleted();

signals:
    void summaryChanged();

private:
    TaskModel m_taskModel;
};
