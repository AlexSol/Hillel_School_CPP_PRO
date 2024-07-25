#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
 
std::once_flag call_flag;
 
void initialize_do_once(int aTaskId)
{
    std::clog << "task id:" << aTaskId <<". thread id:" << std::this_thread::get_id() << std::endl;

    std::call_once(call_flag, [aTaskId](){
        std::clog << "task id:" << aTaskId << ". call_once " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    });
}
 
int main()
{
    std::vector<std::thread> threads;
    for (int taskID{0}; taskID < 5; ++taskID)
    {
        threads.emplace_back(initialize_do_once, taskID);
    }

    for (auto &th : threads)
    {
        th.join();
    }
}