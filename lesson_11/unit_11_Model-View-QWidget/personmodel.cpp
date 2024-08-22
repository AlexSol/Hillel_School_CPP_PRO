#include "personmodel.h"
#include <QBrush>

PersonModel::PersonModel(QObject *parent)
    : QAbstractTableModel(parent) {}

void PersonModel::setPersons(const QList<Person> &persons) {
    beginResetModel(); // Сигналізує про початок оновлення даних
    m_persons = persons;
    endResetModel(); // Сигналізує про завершення оновлення даних
}

int PersonModel::rowCount(const QModelIndex &/*parent*/) const {
    return m_persons.count();
}

int PersonModel::columnCount(const QModelIndex &/*parent*/) const {
    return 2; // Маємо два стовпці: ім'я та вік
}

QVariant PersonModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    const Person &person = m_persons.at(index.row());

    if (role == Qt::DisplayRole) {
        if (index.column() == 0)
            return person.name;
        else if (index.column() == 1)
            return person.age;
    }else if (role == Qt::BackgroundRole) {
        if(person.age >= 30){
            return QBrush(Qt::red);
        }else if(person.age <= 10){
            return QBrush(Qt::magenta);
        }
    }

    return QVariant();
}

QVariant PersonModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            if (section == 0)
                return QString("Name");
            else if (section == 1)
                return QString("Age");
        }
    }
    return QVariant();
}
