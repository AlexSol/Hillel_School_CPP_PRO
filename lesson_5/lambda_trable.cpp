#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <thread>

auto get_lambda()
{
    // 1. Захоплення змінних за посиланням
    int x = 10;
    auto fun = [&x]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << x << std::endl; // Використання x, яка може стати недійсною
    };

    return fun;
}

void lambda_trable_1()
{
    auto fun = get_lambda();
    // Створення нового потоку
    std::thread t(fun);

    // x = 20; // Змінення x у головному потоці
    t.join();
}

struct Person
{
    Person() = default;
    Person(const Person& aPerson)
    : first_name(aPerson.first_name)
    , second_name(aPerson.second_name)
    , phones(aPerson.phones)
    {
        std::clog << "Person. Copy constructor" << std::endl;
    }
    
    std::string first_name;
    std::string second_name;
    std::string address;
    std::string email;
    std::string passport;
    std::vector<std::string> phones;
};


void lambda_trable_2()
{
    // 2. Надмірне захоплення змінних
    Person person;
    person.phones = {"+380501234567", "+380661234511"};

    std::clog<< "sizeof(Person): "<< sizeof(Person) << std::endl;

    auto printPhones = [person]() {
        for (const auto& phone : person.phones) {
            std::cout << phone << std::endl;
        }
    };

    auto printPhonesNoCopy = [&person]() {
        for (const auto& phone : person.phones) {
            std::cout << phone << std::endl;
        }
    };

    std::clog<< "call printPhones\n";
    printPhones();

    std::clog<< std::endl;

    std::clog<< "call printPhonesNoCopy\n";
    printPhonesNoCopy();
}

void lambda_trable_3()
{
    // Ускладнення читабельності коду
    std::vector<int> data = {1, 2, 3, 4, 5};

    std::for_each(data.begin(), data.end(), [&](int& n) {
        n *= 2;
        std::for_each(data.begin(), data.end(), [](int& m) { // Вкладена лямбда-функція
            m += 1;
        });
    });
}

int main() {
    
    // 1. Захоплення змінних за посиланням
    lambda_trable_1();

    std::clog<< "-----------------\n";
    lambda_trable_2(); // 2. Надмірне захоплення змінних

    // Ускладнення читабельності коду
    lambda_trable_3();

    return 0;
}
