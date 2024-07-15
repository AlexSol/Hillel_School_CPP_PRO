#include <iostream>
#include <memory>

class MyClass {
public:
    ~MyClass()
    {
        std::cout << "Destructor of MyClass called." << std::endl;
    }
};

int main() {
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>();
    std::weak_ptr<MyClass> weakPtr = sharedPtr;
    std::cout << "Count of sharedPtr: " << sharedPtr.use_count() << std::endl;
    
    if (auto lockedSharedPtr = weakPtr.lock()) {
        std::cout << "Object is alive." << std::endl;
    } else {
        std::cout << "Object has been destroyed." << std::endl;
    }
    
    sharedPtr.reset(); // Deallocation
    
    if (auto lockedSharedPtr = weakPtr.lock()) {
        std::cout << "Object is alive." << std::endl;
    } else {
        std::cout << "Object has been destroyed." << std::endl;
    }

    return 0;
}