
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QPropertyAnimation>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.resize(250, 150);

    QPushButton button("Start", &window);
    button.setGeometry(50, 50, 100, 50);

    // Створюємо станову машину
    QStateMachine machine;

    // Створюємо перший стан
    QState *state1 = new QState();
    state1->assignProperty(&button, "geometry", QRect(50, 50, 100, 50));
    state1->assignProperty(&button, "text", "State 1");

    // Створюємо другий стан
    QState *state2 = new QState();
    state2->assignProperty(&button, "geometry", QRect(150, 50, 100, 50));
    state2->assignProperty(&button, "text", "State 2");

    // Створюємо третій стан
    QFinalState *finalState = new QFinalState();
    state2->assignProperty(&button, "geometry", QRect(100, 100, 100, 50));
    state2->assignProperty(&button, "text", "Final State");

    // Додаємо переходи між станами
    state1->addTransition(&button, &QPushButton::clicked, state2);
    state2->addTransition(&button, &QPushButton::clicked, finalState);

    // Додаємо стани до машини
    machine.addState(state1);
    machine.addState(state2);
    machine.addState(finalState);
    machine.setInitialState(state1);

    // Додаємо анімацію для переходів
    QPropertyAnimation *animation = new QPropertyAnimation(&button, "geometry");
    animation->setDuration(1000);
    machine.addDefaultAnimation(animation);

    // Починаємо роботу станом машини
    machine.start();

    window.show();
    return app.exec();
}
