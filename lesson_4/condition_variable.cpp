#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void workerFunction() {
    // Робота, яку виконує потік

    // Сигнал про готовність
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one(); // Сповістити інший потік, що робота завершена
}

int main() {
    std::thread worker(workerFunction);

    // Очікування сигналу про готовність від потока worker
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return ready; }); // Чекаємо, поки ready не стане true
    }

    std::cout << "Worker thread has finished its work." << std::endl;

    worker.join();

    return 0;
}
