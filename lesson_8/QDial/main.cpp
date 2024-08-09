#include <QApplication>
#include <QDial>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QDial dial;
    dial.show();

    return app.exec();
}
