#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QQmlContext>

#include "appbackend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    AppBackend appBackend;
    // appBackend.setVersion("0.1.5");
    appBackend.init();
    //всі сигнали і слоти і методи Q_INVOKABLE будеть в глобмальному контексті QML
    // engine.rootContext()->setContextObject(&appBackend);

    engine.rootContext()->setContextProperty("appBackend", &appBackend);


    engine.loadFromModule("unit_11_CPP-QML", "Main");

    QString path = "db_sqllite";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    db.setDatabaseName(path);

    if(db.open())
    {
        QSqlQuery query("create table person "
                        "(id integer primary key, "
                        "firstname varchar(20), "
                        "lastname varchar(30), "
                        "age integer)", db);
    }

    return app.exec();
}
