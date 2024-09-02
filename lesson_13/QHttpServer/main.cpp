#include <QCoreApplication>
#include <QHttpServer>
#include <QHttpServerResponse>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

void printRequest(const QHttpServerRequest &request);

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QHttpServer server;

    // Обробка запиту на кореневий маршрут "/"
    server.route("/", QHttpServerRequest::Method::Get, [](const QHttpServerRequest &request) {

        printRequest(request);
        return QHttpServerResponse("Hello, World!", QHttpServerResponder::StatusCode::Ok);
    });

    // Обробка запиту на маршрут "/json"
    server.route("/json", [](const QHttpServerRequest &request) {

        printRequest(request);

        QJsonObject json;
        json["message"] = "Hello, JSON!";
        return QHttpServerResponse(QJsonDocument(json).toJson(),
                                   QHttpServerResponder::StatusCode::Ok);
    });

    // Запуск сервера на порту 8080
    if (!server.listen(QHostAddress::Any, 8080)) {
        qFatal("Could not start server");
    } else {
        qDebug() << "Server started on port 8080";
    }

    return a.exec();
}

void printRequest(const QHttpServerRequest &request)
{
    qDebug() << "Method:" << request.method();
    qDebug() << "URL:" << request.url().toString();
    qDebug() << "Headers:";

    // Виведення заголовків запиту
    const auto headers = request.headers();
    for (auto [key, value]: headers) {
        qDebug() << key << ":" << value;
    }
}
