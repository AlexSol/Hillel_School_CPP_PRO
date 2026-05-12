#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ModelProvider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ModelProvider provider;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("modelProvider", &provider);

    const QUrl url(QStringLiteral("qrc:/ModelViewShowcase/qml/Main.qml"));
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
