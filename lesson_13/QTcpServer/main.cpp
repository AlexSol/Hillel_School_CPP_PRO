#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDateTime>

class HttpServer : public QTcpServer
{
    Q_OBJECT

public:
    HttpServer(QObject *parent = nullptr) : QTcpServer(parent) {}

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket *socket = new QTcpSocket(this);

        if (socket->setSocketDescriptor(socketDescriptor)) {
            connect(socket, &QTcpSocket::readyRead, this, &HttpServer::handleRequest);
            connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
        } else {
            delete socket;
        }
    }

private slots:
    void handleRequest() {
        QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
        if (!socket)
            return;

        if (socket->canReadLine()) {
            QByteArray request = socket->readAll();
            qDebug() << "Received request:" << request;

            // Простий парсинг HTTP-запиту
            QList<QByteArray> requestLines = request.split('\n');
            if (!requestLines.isEmpty()) {
                QByteArray firstLine = requestLines.first();
                QList<QByteArray> tokens = firstLine.split(' ');

                if (tokens.size() >= 3) {
                    QByteArray method = tokens[0];
                    QByteArray path = tokens[1];
                    QByteArray version = tokens[2];

                    if (method == "GET") {
                        sendResponse(socket, path);
                    } else {
                        sendNotImplemented(socket);
                    }
                }
            }
        }
    }

    void sendResponse(QTcpSocket *socket, const QByteArray &path) {
        // Відповідь на GET-запит
        QByteArray response;
        response.append("HTTP/1.1 200 OK\r\n");
        response.append("Content-Type: text/html\r\n");
        response.append("Connection: close\r\n");
        response.append("\r\n");
        response.append("<html><body><h1>Hello, World!</h1>");
        response.append("<p>Requested path: " + path + "</p>");
        response.append("<p>Current time: " + QDateTime::currentDateTime().toString().toUtf8() + "</p>");
        response.append("</body></html>");

        socket->write(response);
        socket->disconnectFromHost();
    }

    void sendNotImplemented(QTcpSocket *socket) {
        QByteArray response;
        response.append("HTTP/1.1 501 Not Implemented\r\n");
        response.append("Content-Type: text/html\r\n");
        response.append("Connection: close\r\n");
        response.append("\r\n");
        response.append("<html><body><h1>501 Not Implemented</h1></body></html>");

        socket->write(response);
        socket->disconnectFromHost();
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HttpServer server;

    if (!server.listen(QHostAddress::Any, 8080)) {
        qDebug() << "Server could not start!";
        return 1;
    }

    qDebug() << "HTTP Server started on port" << server.serverPort();

    return a.exec();
}

#include "main.moc"
