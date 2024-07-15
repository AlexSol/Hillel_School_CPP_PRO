#include <filesystem>
#include <iostream>
#include <memory>
#include <new>

// no inline, required by [replacement.functions]/3
void* operator new(std::size_t sz)
{
    std::printf("1) new(size_t), size = %zu\n", sz);
    if (sz == 0)
        ++sz; // avoid std::malloc(0) which may return nullptr on success
 
    if (void *ptr = std::malloc(sz))
        return ptr;
 
    throw std::bad_alloc{}; // required by [new.delete.single]/3
}
 
// no inline, required by [replacement.functions]/3
void* operator new[](std::size_t sz)
{
    std::printf("2) new[](size_t), size = %zu\n", sz);
    if (sz == 0)
        ++sz; // avoid std::malloc(0) which may return nullptr on success
 
    if (void *ptr = std::malloc(sz))
        return ptr;
 
    throw std::bad_alloc{}; // required by [new.delete.single]/3
}
 
void operator delete(void* ptr) noexcept
{
    std::puts("3) delete(void*)");
    std::free(ptr);
}
 
void operator delete(void* ptr, std::size_t size) noexcept
{
    std::printf("4) delete(void*, size_t), size = %zu\n", size);
    std::free(ptr);
}
 
void operator delete[](void* ptr) noexcept
{
    std::puts("5) delete[](void* ptr)");
    std::free(ptr);
}
 
void operator delete[](void* ptr, std::size_t size) noexcept
{
    std::printf("6) delete[](void*, size_t), size = %zu\n", size);
    std::free(ptr);
}

struct A
{
    A()     { std::cout << "call  class A(). object: "<< std::endl; };
    ~A()    { std::cout << "call class ~A(). object: "<< std::endl; };
};

void fun_custom_deleter(int* ptr)
{
    std::cout << "destroying from a custom deleter... function\n";
    delete ptr;
}


int main()
{
    try
    {
        A aa = A();
        // A a = A{};
        // auto prt = std::unique_ptr<A>(new A("unique_ptr A"));
        // A* raw_prt = new A{};

        // std::exit(0);
        // throw 1;

        // delete raw_prt;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "catch(..)" << '\n';
    }

    {
        std::unique_ptr<int> prt1 = std::unique_ptr<int>(new int);
        std::unique_ptr<int[]> prt2 = std::unique_ptr<int[]>(new int[10]);

        std::unique_ptr<int> prt3 = std::make_unique<int>();        // C++14
        std::unique_ptr<int[]> prt4 = std::make_unique<int[]>(10);  //C++14

        static_assert(sizeof(prt1) == 8, "sizeof(std::unique_ptr) != 8");
        static_assert(sizeof(prt2) == 8, "sizeof(std::unique_ptr) != 8");
        static_assert(sizeof(prt3) == 8, "sizeof(std::unique_ptr) != 8");
        static_assert(sizeof(prt4) == 8, "sizeof(std::unique_ptr) != 8");


        //custom deleter function
        std::unique_ptr<int, void(*)(int*)> prt_with_deleter_fun1(new int, fun_custom_deleter);
        std::unique_ptr<int, decltype(&fun_custom_deleter)> prt_with_deleter_fun2(new int, &fun_custom_deleter);

        static_assert(sizeof(prt_with_deleter_fun1) == 16, "sizeof(std::unique_ptr + with_deleter_fun) != 16");
        static_assert(sizeof(prt_with_deleter_fun2) == 16, "sizeof(std::unique_ptr + with_deleter_fun) != 16");

        // deleter functor
        struct Deleter
        {
            void operator()(int* ptr)
            {
                std::cout << "destroying from a custom deleter... functor\n";
                delete ptr;
            }
            // int a; // розмір збільшується на 8 байтів. sizeof(unique_ptr) == 16
        };
        std::unique_ptr<int, Deleter> prt_with_deleter_functor(new int);

        static_assert(sizeof(prt_with_deleter_functor) == 8, "sizeof(raw pointer) != 8");

        // deleter Lambda
        std::unique_ptr<int, void(*)(int*)> prt_with_deleter(new int, [](int* ptr)
        {
            std::cout << "destroying from a custom deleter Lambda\n";
            delete ptr;
        });

        auto custom_deleter = [](int* ptr)
        {
            std::cout << "destroying from a custom deleter... Lambda\n";
            delete ptr;
        };

        std::unique_ptr<int, decltype(custom_deleter)> prt_with_deleter2(new int, custom_deleter);

        static_assert(sizeof(prt_with_deleter2) == 8, "sizeof(raw pointer) != 8");

    }

    return 0;
}
