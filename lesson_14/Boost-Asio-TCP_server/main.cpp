#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

void session(tcp::socket socket) {
    try {
        while (true) {
            char data[1024];

            // Читання даних від клієнта
            boost::system::error_code error;
            size_t length = socket.read_some(boost::asio::buffer(data), error);

            if (error == boost::asio::error::eof) {
                std::cout << "Клієнт закрив з'єднання" << std::endl;
                break; // Клієнт закрив з'єднання
            } else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout << "Отримано від клієнта: " << std::string(data, length) << std::endl;

            // Відправка даних назад клієнту
            boost::asio::write(socket, boost::asio::buffer(data, length));
        }
    } catch (std::exception& e) {
        std::cerr << "Помилка у сесії: " << e.what() << std::endl;
    }
}


int main() {
    try {
        // Створюємо I/O контекст
        boost::asio::io_context io_context;

        // Створюємо TCP-акцептор, який слухатиме з'єднання на порту 12345
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

        std::cout << "Сервер запущений і очікує з'єднання на порті 12345..." << std::endl;

        // Цикл для прийому з'єднань
        while (true) {
            // Створюємо сокет для клієнтського з'єднання
            tcp::socket socket(io_context);

            // Чекаємо на клієнтське з'єднання
            acceptor.accept(socket);

            std::cout << "---------- Клієнт підключився! ----------"
                << "\nendpoint:"<<socket.remote_endpoint() << std::endl;

            // Буфер для зберігання отриманого повідомлення
            std::string message = "Hello from TCP server\n";

            // Відправляємо повідомлення клієнту
            boost::asio::write(socket, boost::asio::buffer(message));

            // Буфер для отримання даних від клієнта
            char data[1024];
            boost::system::error_code error;
            size_t length = socket.read_some(boost::asio::buffer(data), error);

            if (!error) {
                std::cout << "Отримано від клієнта: " << std::string(data, length) << std::endl;
            } else {
                std::cout << "Помилка: " << error.message() << std::endl;
            }
            std::cout << "---------- Запит Клієнт  завершився ----------"<< std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }

    return 0;
}
