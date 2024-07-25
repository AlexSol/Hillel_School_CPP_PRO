#include <iostream>
#include <future>
#include <thread>

int fun_sum(int x, int y) {
    
    std::clog<< "call fun_sum. Thread_id:" << std::this_thread::get_id() << std::endl;

    return x + y;
}

int task_bind(int aValue)
{
    std::clog<< "task_bind Thread_id:" << std::this_thread::get_id() << std::endl;
    return 5 * aValue;
}

int main() {
    // Створення packaged_task, який обгортатиме функцію compute
    std::packaged_task<int(int, int)> task(fun_sum);

    // Отримання об'єкта future для отримання результату
    std::future<int> result = task.get_future();

    // Виконання завдання в окремому потоці
    std::thread(std::move(task), 5, 3).detach();

    // Очікування завершення завдання і отримання результату
    std::cout << "Результат: " << result.get() << std::endl;

    {
        std::cout << "\nПриклад запуску в одному потоці" << std::endl;
        std::clog<< "Main Thread_id:" << std::this_thread::get_id() << std::endl;
        std::packaged_task<int(int)> task2(task_bind); 

        std::future<int> result = task2.get_future();
    
        task2(4);
    
        std::cout << "Результат:" << result.get() << '\n';
    }

    return 0;
}
