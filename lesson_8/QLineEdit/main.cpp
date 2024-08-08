#include <QApplication>
#include <QLineEdit>
#include <QDebug>


// textEdited сигнал не видається, коли текст змінюється програмно, наприклад, викликом setText().
// textChanged сигнал видається, коли текст змінюється програмно, наприклад, викликом setText().

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLineEdit lineEdit;

    QLineEdit::connect(&lineEdit, &QLineEdit::textChanged, [](const QString& text){
        qDebug()<< "signal: textChanged. text:" << text << "\n";
    });

    QLineEdit::connect(&lineEdit, &QLineEdit::textEdited, [](const QString& text){
        qDebug()<< "signal: textEdited. text:" << text << "\n";
    });

    lineEdit.show();

    return app.exec();
}
