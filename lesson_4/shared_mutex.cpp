#include <iostream> 
#include <shared_mutex> 
#include <mutex> 
#include <thread> 
using namespace std; 

shared_mutex mutx; 
int shared_data = 11; 

void readData() { 
    shared_lock<shared_mutex> lock(mutx); 
    cout << "Thread " << this_thread::get_id() << ": ";  
    cout << shared_data << endl; 
} 

void writeData(int n) { 
    unique_lock<shared_mutex> lock(mutx); 
    shared_data = n; 
    cout << "Thread" << this_thread::get_id() << ": \n"; 
} 


int main() 
{ 
    thread t1(readData); 
    thread t2(writeData, 128); 
    thread t3(writeData, 10); 
    thread t4 (readData); 
      
    t1.join(); 
    t2.join(); 
    t3.join(); 
    t4.join(); 
    return 0; 
}