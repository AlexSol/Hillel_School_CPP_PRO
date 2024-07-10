#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    fs::path source_path = "source_file.txt";
    fs::path target_path = "target_file.txt";

    try
    {
        fs::copy(source_path, target_path);
        std::cout << "File copied successfully." << std::endl;
    } catch (const fs::filesystem_error& ex)
    {
        std::cerr << "Filesystem error: " << ex.what() << std::endl;
    }
    return 0;
}
