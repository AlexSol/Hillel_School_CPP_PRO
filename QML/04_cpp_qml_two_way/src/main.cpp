#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "BridgeBackend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    BridgeBackend backend;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bridgeBackend", &backend);

    const QUrl url(QStringLiteral("qrc:/CppQmlTwoWay/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app,
                     [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && objUrl == url) {
            QCoreApplication::exit(-1);
        }
    },
                     Qt::QueuedConnection);

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    QObject *root = engine.rootObjects().first();
    QObject::connect(&backend, &BridgeBackend::callQmlFunction, root,
                     [root, &backend](const QString &message) {
        QVariant returned;
        QMetaObject::invokeMethod(root, "qmlCallbackFromCpp",
                                  Q_RETURN_ARG(QVariant, returned),
                                  Q_ARG(QVariant, message));

        backend.onQmlCallback(returned.toString());
    });

    return app.exec();
}
