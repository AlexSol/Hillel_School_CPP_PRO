#include <QApplication>
#include <QPlainTextEdit>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPlainTextEdit plainTextEdit;
    plainTextEdit.show();

    return app.exec();
}
