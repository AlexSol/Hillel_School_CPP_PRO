#include <iostream>
#include <limits>

int main()
{
    volatile int max_value = std::numeric_limits<int>::max();

    std::cout << "About to overflow a signed integer..." << std::endl;
    std::cout << (max_value + 1) << std::endl;

    return 0;
}