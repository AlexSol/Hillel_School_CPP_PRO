#include "BridgeBackend.h"

#include <QDateTime>

BridgeBackend::BridgeBackend(QObject *parent)
    : QObject(parent)
{
}

int BridgeBackend::counter() const
{
    return m_counter;
}

QString BridgeBackend::greet(const QString &name) const
{
    const QString user = name.trimmed().isEmpty() ? QStringLiteral("student") : name.trimmed();
    return QStringLiteral("Hello from C++, %1!").arg(user);
}

void BridgeBackend::incrementCounter()
{
    ++m_counter;
    emit counterChanged();
    emit cppMessage(QStringLiteral("Counter in C++ changed to %1").arg(m_counter));
}

void BridgeBackend::sendToCpp(const QString &message)
{
    emit cppMessage(QStringLiteral("QML -> C++: %1").arg(message));
}

void BridgeBackend::askQmlToRespond()
{
    const QString stamp = QDateTime::currentDateTime().toString(Qt::ISODate);
    emit callQmlFunction(QStringLiteral("Please process this in QML. Timestamp: %1").arg(stamp));
}

void BridgeBackend::onQmlCallback(const QString &message)
{
    emit cppMessage(QStringLiteral("QML callback received in C++: %1").arg(message));
}
