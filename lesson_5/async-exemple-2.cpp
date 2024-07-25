#include <iostream>
#include <future>
#include <chrono>

int long_computation() {
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Симуляція довготривалої операції
    return 42;
}

int main() {
    std::cout << "Запуск асинхронного завдання..." << std::endl;
    std::future<int> result = std::async(std::launch::async, long_computation);

    std::cout << "Продовження виконання в головному потоці..." << std::endl;

    // Отримання результату виконання асинхронного завдання
    int value = result.get(); // Блокує до завершення завдання і повертає результат
    std::cout << "Результат асинхронного завдання: " << value << std::endl;

    return 0;
}
