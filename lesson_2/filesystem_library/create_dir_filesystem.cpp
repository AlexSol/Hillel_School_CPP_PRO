// створення папки std::filesystem

#include <iostream>
#include <filesystem>

int main()
{
    std::string dir_path = "example_directory";

    bool success = std::filesystem::create_directory(dir_path);
    if (!success)
	{
        std::cerr << "Failed to create directory." << std::endl;
        return 1;
    }

    std::cout << "Directory created successfully." << std::endl;
    return 0;
}