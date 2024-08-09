#include <QApplication>
#include <QPushButton>
#include <QIcon>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    QPushButton button(QIcon("icon-tools.png"), "Styled Button");
    button.setStyleSheet("QPushButton { background-color: blue; color: white; }");

    // button.setIconSize(QSize(50 ,50));
    button.show();

    return app.exec();
}
