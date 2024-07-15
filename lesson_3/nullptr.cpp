#include <iostream>

void foo(int ptr) {
    std::cout << "foo(int)" << std::endl;
}

void foo(int* ptr) {
    std::cout << "foo(int*)" << std::endl;
}

void foo(std::nullptr_t ptr) {
    std::cout << "foo(nullptr)" << std::endl;
}

// #define NULL 0
//since C++11
// #define NULL nullptr

int main() {

    {
        // const int * ptr = new int(10);
        // int const * ptr = new int(10);
        int * const ptr = new int(10);
        
        std::cout << "ptr: " << ptr << std::endl;
        std::cout << "value: " << *ptr << std::endl;

        *ptr = 20; //error: read-only variable is not assignable

        // ptr = new int(30); //error: assignment of read-only variable 'ptr'

        std::cout << "value: " << *ptr << std::endl;
    }

    int ver_int = 10;
    int* ptr1 = nullptr;
    int* ptrNULL = 0;

    foo(ptr1);      // Calls foo(int*)
    foo(ptrNULL);   // Calls foo(int*)
    foo(ver_int);   // Calls foo(int)

    return 0;
}