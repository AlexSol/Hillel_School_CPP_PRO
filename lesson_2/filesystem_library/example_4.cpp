// Створення файлу std::filesystem

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main()
{
    std::string file_path = "example.txt";
    try
   {
        fs::create_file(file_path);
        std::cout << "File created successfully." << std::endl;
    } catch (const fs::filesystem_error& ex)
   {
        std::cerr << "Filesystem error: " << ex.what() << std::endl;
    }

    return 0;
}
