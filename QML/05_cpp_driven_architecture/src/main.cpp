#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "AppController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    AppController controller;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("appController", &controller);

    const QUrl url(QStringLiteral("qrc:/CppDrivenArchitecture/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app,
                     [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && objUrl == url) {
            QCoreApplication::exit(-1);
        }
    },
                     Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
