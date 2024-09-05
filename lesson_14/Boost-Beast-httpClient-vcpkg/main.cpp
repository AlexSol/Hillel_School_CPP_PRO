#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/beast/version.hpp>
#include <boost/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

namespace beast = boost::beast;           // Boost.Beast
namespace http = beast::http;             // HTTP протокол
namespace net = boost::asio;              // Boost.Asio
using tcp = net::ip::tcp;                 // TCP протокол

int main() {

    std::cout << "Boost version: " << BOOST_VERSION << std::endl;

    try {
        // IO контекст для керування операціями
        net::io_context ioc;

        // Резолвер для знаходження IP за ім'ям хоста
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve("example.com", "80");

        // Створення TCP сокету
        tcp::socket socket(ioc);

        // Підключення до сервера
        net::connect(socket, results.begin(), results.end());

        // Створення HTTP запиту
        http::request<http::string_body> req{http::verb::get, "/", 11};
        req.set(http::field::host, "example.com");
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Надсилання запиту через сокет
        http::write(socket, req);

        // Буфер для зберігання відповіді
        beast::flat_buffer buffer;

        // Об'єкт для збереження HTTP відповіді
        http::response<http::dynamic_body> res;

        // Читання відповіді
        http::read(socket, buffer, res);

        // Виведення відповіді
        std::cout << res << std::endl;

        // Закриття сокету
        beast::error_code ec;
        socket.shutdown(tcp::socket::shutdown_both, ec);

        if (ec && ec != beast::errc::not_connected) {
            throw beast::system_error{ec};
        }

    } catch (std::exception const& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
