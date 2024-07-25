#include <iostream>
#include <thread>
#include <future>

void compute(std::promise<int>& prom, int a, int b) {
    try {
        int result = a + b;
        prom.set_value(result); // Встановлення значення
    } catch (...) {
        prom.set_exception(std::current_exception()); // Передача виключення
    }
}

int main() {
    std::promise<int> prom; // Створення promise
    std::future<int> fut = prom.get_future(); // Отримання future

    std::thread t(compute, std::ref(prom), 10, 20); // Запуск потоку з передачею promise

    try {
        int result = fut.get(); // Отримання результату
        std::cout << "Результат: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Виключення: " << e.what() << std::endl;
    }

    t.join(); // Очікування завершення потоку

    return 0;
}
