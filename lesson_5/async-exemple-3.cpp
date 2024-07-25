#include <iostream>
#include <future>
#include <stdexcept>

int faulty_function() {
    std::cout << "Start faulty_function" << std::endl;
    throw std::runtime_error("Error in faulty_function");
}

int main() {
    std::future<int> result = std::async(std::launch::async, faulty_function);

    try {
        int value = result.get(); // Блокує і передає виключення
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
