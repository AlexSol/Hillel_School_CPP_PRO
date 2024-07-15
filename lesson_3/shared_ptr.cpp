#include <iostream>
#include <string>
#include <memory>

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

struct Player
{
  std::shared_ptr<Player> companion; // рішення замінити на weak_ptr
  ~Player() { std::cout << "~Player\n"; }
};

struct Base
{
    Base() { std::cout << "Base::Base()\n"; }
 
    // Note: non-virtual destructor is OK here
   ~Base() { std::cout << "Base::~Base()\n"; }
};
 
struct Derived : public Base
{
    Derived() { std::cout << "Derived::Derived()\n"; }
 
    ~Derived() { std::cout << "Derived::~Derived()\n"; }
};


class Confing
{
public:
    Confing() = default;
    ~Confing() = default;
    void print() { std::cout << "Config data\n"; }
};

class Component
{
public:
    Component(const std::string& name, std::shared_ptr<Confing> config)
    : m_name{name}
    , m_config{config} {}
    
    ~Component() = default;

    void print() {
        std::cout << "Component name: " << m_name << std::endl;
         m_config->print();
    }
    
    std::string m_name;
    std::shared_ptr<Confing> m_config;
};

int main() {

    //типовий приклад використання shared_ptr.
    // shared_ptr використовується для передачі власності об'єкта
    // між різними частинами програми
    std::shared_ptr<Confing> config = std::make_shared<Confing>();
    std::shared_ptr<Component> component1 = std::make_shared<Component>("component-1", config);
    std::shared_ptr<Component> component2 = std::make_shared<Component>("component-2", config);

    component1->print();
    component2->print();

    return 0;
    // std::shared_ptr<Base> sp0 = std::shared_ptr<Derived>(new Derived());/
    std::shared_ptr<Base> sp1 = std::make_shared<Derived>();

    static_assert(sizeof(sp1) == 16, "sizeof(std::shared_ptr) != 16");

    return 0;
    // проблематика циклічних посилань
    {
        std::shared_ptr<Player> jasmine = std::make_shared<Player>();
        std::shared_ptr<Player> albert  = std::make_shared<Player>();

        jasmine->companion = albert; // (1)
        albert->companion  = jasmine; // (2)
    }

    return 0;
}