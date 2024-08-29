#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.resize(250, 150);

    QPushButton button("Animate", &window);
    button.setGeometry(10, 10, 100, 30);

    // Створення анімації для зміни положення кнопки
    QPropertyAnimation animation(&button, "geometry");
    animation.setDuration(1000); // тривалість анімації (в мілісекундах)
    animation.setStartValue(QRect(10, 10, 100, 30)); // початкове положення кнопки
    animation.setEndValue(QRect(150, 80, 100, 30)); // кінцеве положення кнопки

    // При кліку на кнопку починаємо анімацію
    QObject::connect(&button, &QPushButton::clicked, [&animation]() {
        animation.start();
    });

    window.show();

    return app.exec();
}


