#include <iostream>
#include <vector>

typedef std::vector<int>::iterator IntIterator;

int main()
{
    int* ptr = NULL;

    if (ptr == NULL)
    {
        std::cout << "ptr is null" << std::endl;
    }

    std::vector<int> values = {1, 2, 3};
    IntIterator it = values.begin();

    std::cout << *it << std::endl;
    return 0;
}
