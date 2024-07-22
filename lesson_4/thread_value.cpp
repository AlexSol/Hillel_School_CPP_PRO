#include <iostream>
#include <thread>
#include <string>

void printMessage(const std::string& message) {  //Копія
   std::clog<< message << std::endl;
}

int main() {
    std::string message = "Hello from main thread!";
    std::thread tr(printMessage, message);
    tr.join();

    return 0;
}
