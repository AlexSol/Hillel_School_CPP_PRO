#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.resize(400, 300);

    QLabel label("Click the button to start", &window);
    label.setGeometry(50, 50, 300, 50);

    QPushButton button("Start", &window);
    button.setGeometry(150, 150, 100, 50);

    // Створюємо станову машину
    QStateMachine machine;

    // Створюємо стани
    QState *state1 = new QState();
    QState *state2 = new QState();
    QFinalState *finalState = new QFinalState();

    // Визначення властивостей для станів
    state1->assignProperty(&label, "text", "In State 1");
    state2->assignProperty(&label, "text", "In State 2");

    // Визначення переходів з умовами і діями
    QSignalTransition *transition1 = state1->addTransition(&button, &QPushButton::clicked, state2);
    transition1->addAnimation(new QPropertyAnimation(&button, "geometry", state1));
    transition1->addAnimation(new QPropertyAnimation(&label, "geometry", state1));

    QSignalTransition *transition2 = state2->addTransition(&button, &QPushButton::clicked, finalState);
    transition2->addAnimation(new QPropertyAnimation(&button, "geometry", state2));
    transition2->addAnimation(new QPropertyAnimation(&label, "geometry", state2));

    // Призначення дій при активації переходів
    QObject::connect(transition1, &QSignalTransition::triggered, [&]() {
        button.setText("Next");
    });
    QObject::connect(transition2, &QSignalTransition::triggered, [&]() {
        button.setText("Done");
    });

    // Додаємо стани до машини
    machine.addState(state1);
    machine.addState(state2);
    machine.addState(finalState);
    machine.setInitialState(state1);

    // Починаємо роботу станом машини
    machine.start();

    window.show();
    return app.exec();
}
