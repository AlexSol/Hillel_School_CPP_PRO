#include <iostream>

int main()
{
    volatile int* dangling = nullptr;

    auto* values = new int[4]{10, 20, 30, 40};
    dangling = values;

    delete[] values;

    std::cout << "Writing into freed memory..." << std::endl;
    dangling[0] = 50;
    std::cout << dangling[0] << std::endl;

    return 0;
}