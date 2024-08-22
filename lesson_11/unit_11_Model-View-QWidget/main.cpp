#include <QApplication>
#include <QTableView>
#include "personmodel.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Створюємо модель
    PersonModel model;

    // Додаємо дані в модель
    QList<Person> persons;
    persons.append({"John Doe 2", 7});
    persons.append({"John Doe", 30});
    persons.append({"Jane Smith", 28});
    persons.append({"Sam Brown", 22});

    model.setPersons(persons);

    // Створюємо подання для відображення даних
    QTableView view;
    view.setModel(&model);
    view.show();

    return app.exec();
}
