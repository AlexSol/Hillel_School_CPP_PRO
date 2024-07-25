#include <iostream>
#include <future>
#include <thread>
#include <vector>

int long_computation() {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Симуляція довготривалої операції
    return 42;
}

void worker(std::shared_future<int> shared_fut, int id) {
    std::clog<< "Потік " << id << " почав виконання" << std::endl;
    
    try {
        int result = shared_fut.get(); // Отримання результату
        std::clog << "Потік " << id << " отримав результат: " << result << std::endl;
    } catch (const std::exception& e) {
        std::clog << "Потік " << id << " отримав виключення: " << e.what() << std::endl;
    }
}

int main() {
    // Запуск асинхронного завдання
    std::future<int> fut = std::async(std::launch::async, long_computation);
    std::shared_future<int> shared_fut = fut.share(); // Перетворення на shared_future

    // Запуск декількох потоків, що отримують результат
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(worker, shared_fut, i);
    }

    for (auto& t : threads) {
        t.join(); // Очікування завершення всіх потоків
    }

    return 0;
}
