#include <iostream>
#include <thread>
#include <mutex>

// std::scoped_lock - C++17,
// дозволяє блокувати кілька мутексів одночасно.
// Він гарантує безпечний захват всіх переданих мутексів,
// намагаючись уникнути потенційних проблем, таких як deadlock.


std::mutex mtx1, mtx2;

void threadFunction() {
    std::scoped_lock lock(mtx1, mtx2); // Захоплення 
    std::cout << "Thread ID: " 
      << std::this_thread::get_id() << std::endl;
}

int main() {
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);

    t1.join();
    t2.join();

    return 0;
}
