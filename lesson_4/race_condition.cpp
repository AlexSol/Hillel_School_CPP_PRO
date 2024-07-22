#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

int counter = 0;


void increment()
{

    for (int i = 0; i < 100000; ++i) {
          mtx.lock();
          
          // std::this_thread::sleep_for(std::chrono::microseconds(10));
          // std::lock_guard<std::mutex> lock(mtx);
          ++counter; // This operation // is not atomic
          
          mtx.unlock();
    }
}


int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter value: " << counter << std::endl;

    return 0;
}
