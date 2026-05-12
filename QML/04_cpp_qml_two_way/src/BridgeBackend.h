#pragma once

#include <QObject>

class BridgeBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int counter READ counter NOTIFY counterChanged)

public:
    explicit BridgeBackend(QObject *parent = nullptr);

    int counter() const;

    Q_INVOKABLE QString greet(const QString &name) const;
    Q_INVOKABLE void incrementCounter();
    Q_INVOKABLE void sendToCpp(const QString &message);
    Q_INVOKABLE void askQmlToRespond();

signals:
    void counterChanged();
    void cppMessage(const QString &message);
    void callQmlFunction(const QString &message);

public slots:
    void onQmlCallback(const QString &message);

private:
    int m_counter = 0;
};
