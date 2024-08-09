#include <QApplication>
#include <QDateTimeEdit>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QDateTimeEdit dateTimeEdit;
    dateTimeEdit.show();

    return app.exec();
}
