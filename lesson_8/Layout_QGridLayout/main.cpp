#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QGridLayout *layout = new QGridLayout(&window);

    layout->addWidget(new QPushButton("Button 1"), 0, 0);
    layout->addWidget(new QPushButton("Button 2"), 0, 1);
    layout->addWidget(new QPushButton("Button 3"), 1, 0);
    layout->addWidget(new QPushButton("Button 4"), 1, 1);

    window.show();

    return app.exec();
}
