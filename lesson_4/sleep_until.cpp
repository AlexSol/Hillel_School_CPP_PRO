#include <iostream>
#include <thread>
#include <chrono>

void printCurrentTime()
{
    auto time_now = std::chrono::system_clock::now();
    auto current_time = std::chrono::system_clock::to_time_t(time_now);
    std::cout << "Current time: " << std::ctime(&current_time);
}

int main()
{
    // Get the current time
    auto time_now = std::chrono::system_clock::now();

    // Calculate the time 5 seconds from now
    auto timeToWakeUp = time_now + std::chrono::seconds(5);

    // Print the current time
    std::cout << "Before sleep_until(): ";
    
    printCurrentTime();

    // Sleep until the calculated time
    std::this_thread::sleep_until(timeToWakeUp);

    // Print the current time after waking up
    std::cout << "After sleep_until(): ";
    
    printCurrentTime();
    
    return 0;
}
