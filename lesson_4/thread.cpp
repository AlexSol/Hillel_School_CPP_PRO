#include <thread>
#include <iostream> 

void actionsInThread()
{
     std::cout<< "call fun from thread. " << "Thread id:" << std::this_thread::get_id() << "\n";
}
 
int main()
{
    std::cout<< "start main Thread. Id:" << std::this_thread::get_id() << "\n";

     std::thread myTread(actionsInThread);
     std::cout<< "created myTread id:"<< myTread.get_id() << "\n";


    // myTread.join();
    myTread.detach();

    std::cout<< "end main Thread. Id:" << std::this_thread::get_id() << "\n";

     return 0;
}
