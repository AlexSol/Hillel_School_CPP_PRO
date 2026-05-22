#include <iostream>
#include <sanitizer/lsan_interface.h>

__attribute__((noinline)) void create_leak()
{
    auto* data = new int[128];

    data[0] = 42;
    std::cout << "Allocated array starts with: " << data[0] << std::endl;
}

__attribute__((noinline)) void scrub_stack()
{
    volatile char buffer[4096];

    for (int index = 0; index < 4096; ++index)
    {
        buffer[index] = 0;
    }
}

int main()
{
    create_leak();
    scrub_stack();
    std::cout << "Memory is intentionally not released." << std::endl;
    __lsan_do_leak_check();

    return 0;
}