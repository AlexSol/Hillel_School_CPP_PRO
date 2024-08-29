#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

    int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.resize(250, 150);

    QPushButton button("Animate", &window);
    button.setGeometry(10, 10, 100, 30);

    // Створення анімації для зміни прозорості кнопки
    QPropertyAnimation *opacityAnimation = new QPropertyAnimation(&button, "windowOpacity");
    opacityAnimation->setDuration(1000); // тривалість анімації (в мілісекундах)
    opacityAnimation->setStartValue(1.0); // початкова прозорість кнопки
    opacityAnimation->setEndValue(0.2); // кінцева прозорість кнопки

    // Створення анімації для зміни розміру кнопки
    QPropertyAnimation *sizeAnimation = new QPropertyAnimation(&button, "geometry");
    sizeAnimation->setDuration(1000); // тривалість анімації (в мілісекундах)
    sizeAnimation->setStartValue(QRect(10, 10, 100, 30)); // початковий розмір кнопки
    sizeAnimation->setEndValue(QRect(150, 80, 200, 50)); // кінцевий розмір кнопки

    // Група послідовних анімацій
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(&window);
    group->addAnimation(opacityAnimation);
    group->addAnimation(sizeAnimation);

    // При кліку на кнопку починаємо анімацію
    QObject::connect(&button, &QPushButton::clicked, [&group](){
        group->start();
    });

    window.show();

    return app.exec();
}


