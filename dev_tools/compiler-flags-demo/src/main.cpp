#include <iostream>

#include "visibility_demo.hpp"

int main()
{
    const int a = 7;
    const int b = 3;

    std::cout << "public_sum(" << a << ", " << b << ") = " << public_sum(a, b) << '\n';
    std::cout << "hidden_subtract is intentionally hidden and not part of external API" << '\n';
    return 0;
}