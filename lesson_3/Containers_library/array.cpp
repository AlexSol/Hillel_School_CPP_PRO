#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>

void printArray(const auto& vec)
{
    for (auto& n : vec)
        std::cout << n << ' ';
    
    std::cout << '\n';   
}
//----------------
// Element access
// at()
// operator[]
// front()
// back()
// data()

// empty
// size
// fill

int main()
{
    //способи створення array
    std::array<int, 3> a1{{1, 2, 3}};
    //std::array<int, 3> a2 = {1, 2, 3};

    std::cout<< "size: " << a1.size() << std::endl;
    std::cout<< "empty: " << a1.empty() << std::endl;

    printArray(a1);

    // перевіряємо метод fill()
    a1.fill(10);
    printArray(a1);

    // доступ по індексу
    std::cout<< a1.at(0) << std::endl;
    std::cout<< a1[0] << std::endl;

    // спроба звернутися до елементу за межами масиву
    try
    {
        std::cout<< a1.at(100) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        std::cout<< a1[10000] << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "catch(...) \n";
    }
    

    // printArray(a1);
}