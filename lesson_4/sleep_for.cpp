#include <iostream>
#include <thread>
#include <chrono>

void countdown(int seconds)
{
    for (int i = seconds; i > 0; --i) {
        std::cout << i << " seconds remaining...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    }
    std::cout << "Countdown complete!\n";
}

int main()
{
    std::thread t(countdown, 5 );
    t.join();
//     t.detach();

     std::cout << "end main thread\n";
    return 0;
}
