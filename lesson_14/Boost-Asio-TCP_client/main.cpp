#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int main() {
    try {
        // Створюємо I/O контекст
        boost::asio::io_context io_context;

        // Створюємо резолвер для визначення адреси сервера
        tcp::resolver resolver(io_context);

        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "12345");

        // Створюємо сокет
        tcp::socket socket(io_context);

        // Підключаємось до сервера
        boost::asio::connect(socket, endpoints);

        // Буфер для отримання повідомлення від сервера
        char reply[1024];
        size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply, 1024));

        std::cout << "Отримано від сервера: " << std::string(reply, reply_length) << std::endl;

        // Відправляємо повідомлення серверу
        std::string message = "Hello from TCP client";
        boost::asio::write(socket, boost::asio::buffer(message));

    } catch (std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }

    return 0;
}
