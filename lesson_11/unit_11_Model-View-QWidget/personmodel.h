#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QAbstractTableModel>
#include <QString>

struct Person {
    QString name;
    int age;
};

class PersonModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit PersonModel(QObject *parent = nullptr);

    // Встановлення даних у модель
    void setPersons(const QList<Person> &persons);

    // Методи, які потрібно реалізувати для успадкування від QAbstractTableModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<Person> m_persons; // Список об'єктів Person
};

#endif // PERSONMODEL_H
