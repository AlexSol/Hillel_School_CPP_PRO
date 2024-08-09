#include <QApplication>
#include <QProgressBar>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QProgressBar progressBar;
    progressBar.setValue(5);
    progressBar.show();

    return app.exec();
}
