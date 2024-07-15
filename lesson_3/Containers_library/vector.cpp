#include <iostream>
#include <vector>

void printArray(const auto& vec)
{
    for (auto& n : vec)
        std::cout << n << ' ';
    
    std::cout << '\n';   
}
//----------------
struct A
{
    A()     { std::cout << "call  class A(). object: "<< std::endl; };
    ~A()    { std::cout << "call class ~A(). object: "<< std::endl; };
};
// -----------------
// at
// operator[]
// front
// back
// data

// Capacity
// empty
// size
// clear
// reserve
// capacity
// resize
// emplace (C++11)
// emplace_back (C++11)
// push_back
// pop_back
 

int main()
{
    std::vector<int> vec(10);
    //std::vector<int> vec(10, 1);
    // std::vector<int> vec = {8, 4, 5, 9};

    // vec.push_back(6);
    // vec.push_back(9);
 
    try
    {
        // vec[-1] = -1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
 
    printArray(vec);

    // -------------------
    {
        A a  = A();
        // std::vector<A> vec;
        // vec.push_back(A());
        // vec.emplace_back(std::move(A()));

    }
}