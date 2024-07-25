#include <iostream>
#include <vector>
#include <algorithm>

void fun_print(int n) {
    std::cout << n << " ";
}

int main() {

    // 0. як ми писали до С++11(лямбда-функція)
    //присклад з функцією
    {
        std::cout << "Lumbda. Присклад з функцією\n";

        std::vector<int> numbers = {1, 2, 3, 4, 5};
        std::for_each(numbers.begin(), numbers.end(), fun_print);

        std::cout << "\n";
    }
    // приклад з функтором
    {
        std::cout << "Lumbda. Присклад з функтором\n";

        struct FunPrint {
            void operator()(int n) {
                std::cout << n << " ";
            }
        };

        std::vector<int> numbers = {1, 2, 3, 4, 5};
        std::for_each(numbers.begin(), numbers.end(), FunPrint());

        std::cout << "\n";
    }

    // 1. Проста лямбда-функція

    auto fun_lambda = []() {
        std::cout << "Lambda, Hello, World!" << std::endl;
    };

    fun_lambda();

// ----------
    //typedef void(*lambdaFn)();
    using LambdaFnT = void(*)(); // інший синтаксис запиче без typedef

    LambdaFnT fun_lambda2 = []() {
        std::cout << "Lambda 2, Hello, World!" << std::endl;
    };

    fun_lambda2();
    
    // 2. Лямбда-функція з параметрами і типом повертаємого значення
    auto add = [](int a, int b) -> int {
        return a + b;
    };

    int result = add(3, 4); // Виклик лямбда-функції з параметрами
    std::cout << "3 + 4 = " << result << std::endl;

    // 3. Лямбда-функція з захопленням змінних
    {
        int x = 10;
        int y = 20;

        auto add = [x, y]() -> int {
            return x + y;
        };

        std::cout << "x + y = " << add() << std::endl; // Виклик лямбда-функції
    }

    // 4. Захоплення змінних за значенням і за посиланням
    {
        int x = 10;
        int y = 20;

        auto add = [=, &y]() -> int {
            y = 30; // y захоплено за посиланням, тому його можна змінити
            return x + y; // x захоплено за значенням, тому його не можна змінити
        };

        std::cout << "x + y = " << add() << std::endl;
        std::cout << "y після лямбда-функції: " << y << std::endl; // y змінено
    }

    // 5. Використання лямбда-функції з алгоритмами STL
    {
        std::vector<int> numbers = {1, 2, 3, 4, 5};

        std::for_each(numbers.begin(), numbers.end(), [](int n) {
            std::cout << n << " ";
        });
    }

    return 0;
}
