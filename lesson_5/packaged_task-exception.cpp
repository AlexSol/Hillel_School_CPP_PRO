#include <iostream>
#include <future>
#include <thread>
#include <stdexcept>

int faulty_function(int x) {
    if (x < 0) {
        throw std::runtime_error("Negative value not allowed!");
    }
    return x * 2;
}

int main() {
    std::packaged_task<int(int)> task(faulty_function);
    
    std::future<int> result = task.get_future();
    
    std::thread(std::move(task), -5).detach();

    try {
        int value = result.get();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0;
}