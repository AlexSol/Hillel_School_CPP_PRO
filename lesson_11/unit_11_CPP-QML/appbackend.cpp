#include "appbackend.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

AppBackend::AppBackend(QObject *parent)
    : QObject{parent}
{}

void AppBackend::userLogin(const QString& aUserName)
{
    const auto foundUser = m_credentials.find(aUserName);
    if(foundUser == m_credentials.end())
    {
        emit loginResult(-1,"Помилка. відсутрій користувач:" + aUserName);
    }
    else
    {
        emit loginResult(0, "вхід успішний");
    }
}

void AppBackend::setVersion(const QString& aVersion)
{
    if(m_version != aVersion){
        m_version = aVersion;
        qDebug()<< "emit versionChanged(aVersion):" << aVersion;
        emit versionChanged(m_version);
    };
}

int AppBackend::init()
{
    // Відкриваємо JSON-файл
    QFile file(credentialsFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не вдалося відкрити файл";
        return -1;
    }

    // Зчитуємо вміст файлу
    QByteArray fileData = file.readAll();
    file.close();

    // Парсимо JSON-документ
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);

    // Перевіряємо, чи це масив
    if (!jsonDoc.isArray()) {
        qWarning() << "JSON не є масивом";
        return -1;
    }

    // Отримуємо масив
    QJsonArray jsonArray = jsonDoc.array();

    // Проходимося по масиву і виводимо дані
    for (const QJsonValue &value : jsonArray) {
        // Перевіряємо, чи елемент є об'єктом
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            QString login = obj["login"].toString();
            QString password = obj["password"].toString();

            qDebug() << "Login:" << login << ", Password:" << password;

            m_credentials.insert(login, password);
        }
    }

    return 0;
}
