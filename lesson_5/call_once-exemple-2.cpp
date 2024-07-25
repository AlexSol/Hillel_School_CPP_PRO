#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
 
std::once_flag call_flag;
  
void may_throw_function(bool do_throw)
{
    if (do_throw)
    {
        std::cout << "Throw: call_once will retry\n";
        throw std::exception();
    }
    std::cout << "Did not throw, call_once will not attempt again\n";
}
 
void do_once(bool do_throw)
{
    try
    {
        std::call_once(call_flag, may_throw_function, do_throw);
    }
    catch (...) {}
}
 
int main()
{
    std::thread th1(do_once, true);
    std::thread th2(do_once, true);
    std::thread th3(do_once, false);
    std::thread th4(do_once, true);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
}