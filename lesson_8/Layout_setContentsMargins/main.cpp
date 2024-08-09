#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

// Масштабування виджетів:
// - Використання мінімальних, максимальних та фіксованих розмірів (`setMinimumSize`, setMaximumSize, `setFixedSize`).
// - Використання розтягуваності в макетах (`setStretch`).

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);

    QPushButton *button1 = new QPushButton("Button 1");
    QPushButton *button2 = new QPushButton("Button 2");

    layout->addWidget(button1);
    layout->addWidget(button2);

    button1->setMinimumSize(100, 50);
    button1->setMaximumSize(200, 400);

    layout->setContentsMargins(10, 20, 30, 40);

    window.show();

    return app.exec();
}
