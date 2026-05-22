#include <iostream>
#include <thread>

namespace
{
int shared_counter = 0;
}

void increment_counter()
{
    for (int i = 0; i < 100000; ++i)
    {
        ++shared_counter;
    }
}

int main()
{
    std::thread first_worker(increment_counter);
    std::thread second_worker(increment_counter);

    first_worker.join();
    second_worker.join();

    std::cout << "Final counter value: " << shared_counter << std::endl;
    return 0;
}