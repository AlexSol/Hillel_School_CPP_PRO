#include <iostream>

struct Root
{
    void foo()
    {
        std::cout << "Root::foo()" << std::endl;
    }
};


struct B : public Root
{
    void foo()
    {
        std::cout << "B::foo()" << std::endl;
    }
};


int main()
{
    Root* a = new B();

    a->foo();

    return 0;
}