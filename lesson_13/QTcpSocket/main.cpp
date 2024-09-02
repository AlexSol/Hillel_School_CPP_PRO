#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpSocket socket;

    // Підключаємося до сервера
    socket.connectToHost("example.com", 80);

    // Перевіряємо, чи з'єднання встановлено
    if (!socket.waitForConnected(3000)) {
        qDebug() << "Connection failed:" << socket.errorString();
        return -1;
    }

    qDebug() << "Connected to server";

    // Відправляємо HTTP-запит
    socket.write("GET / HTTP/1.1\r\nHost: example.com\r\n\r\n");

    // Чекаємо поки дані будуть відправлені
    if (!socket.waitForBytesWritten(3000)) {
        qDebug() << "Failed to send data:" << socket.errorString();
        return -1;
    }

    // Чекаємо відповіді від сервера
    if (!socket.waitForReadyRead(3000)) {
        qDebug() << "No response received:" << socket.errorString();
        return -1;
    }

    // Читаємо відповідь
    QByteArray responseData = socket.readAll();
    qDebug() << "Response from server:" << responseData;

    // Закриваємо з'єднання
    socket.disconnectFromHost();

    return a.exec();
}
