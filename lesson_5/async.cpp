#include <iostream>
#include <future>
#include <thread>
#include <atomic>
#include <random>

bool my_task(std::size_t aTaskId)
{
    std::clog<< "Task:" << aTaskId << " started\n"
    << "thread_id:" << std::this_thread::get_id() << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 5);

    std::this_thread::sleep_for(std::chrono::seconds(dis(gen)));

    std::clog<< "Task:" << aTaskId << " finished" << std::endl;

    return true;
}


int main()
{
    std::clog<< "Main Thread_id:" << std::this_thread::get_id() << std::endl;

    std::future<bool> task1 = std::async(my_task, 1);
    std::future<bool> task2 = std::async(my_task, 2);

    task1.wait();
    task2.wait();

    std::clog<< "Main thread done!" << std::endl;

    return 0;
}
