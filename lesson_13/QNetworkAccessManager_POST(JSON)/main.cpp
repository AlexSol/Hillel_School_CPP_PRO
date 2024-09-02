#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://echo.free.beeceptor.com"));

    // Встановлюємо заголовок для вказівки типу даних
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Створюємо JSON-об'єкт для відправки
    QJsonObject json;
    json["key1"] = "value1";
    json["key2"] = "value2";

    // Конвертуємо JSON-об'єкт в QByteArray
    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    // Виконуємо POST-запит
    QNetworkReply *reply = manager.post(request, jsonData);

    // Підключаємо сигнал для отримання відповіді
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if(reply->error() == QNetworkReply::NoError) {
            // Отримуємо відповідь від сервера
            QByteArray responseData = reply->readAll();
            qDebug() << "Response:" << responseData;
        } else {
            // Виводимо помилку
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater(); // Очищуємо пам'ять
    });

    return a.exec();
}
