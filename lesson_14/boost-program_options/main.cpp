#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    // Створюємо об'єкт для зберігання опцій
    po::options_description desc("Доступні опції");

    // Додаємо опції
    desc.add_options()
        ("help,h", "Вивести довідку")
        ("filename,f", po::value<std::string>(), "Вказати ім'я файлу")
        ("threads,t", po::value<int>()->default_value(4), "Кількість потоків");

    // Створюємо об'єкт для зберігання результатів парсингу
    po::variables_map vm;

    // Парсимо аргументи командного рядка
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);  // Застосовуємо значення
    } catch (const po::error& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
        return 1;
    }

    // Якщо вказано опцію --help, виводимо допомогу
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    // Якщо вказано опцію --filename, виводимо ім'я файлу
    if (vm.count("filename")) {
        std::cout << "Ім'я файлу: " << vm["filename"].as<std::string>() << std::endl;
    } else {
        std::cout << "Файл не вказано" << std::endl;
    }

    // Виводимо кількість потоків (якщо не вказано, використовується значення за замовчуванням)
    std::cout << "Кількість потоків: " << vm["threads"].as<int>() << std::endl;

    return 0;
}
