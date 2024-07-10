#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    std::filesystem::path directory_path = "..";

    try
    {
        // Check if the directory exists
        if (std::filesystem::exists(directory_path) && std::filesystem::is_directory(directory_path))
        {
            // Iterate over the files in the directory
            for (const auto& entry : std::filesystem::directory_iterator(directory_path))
            {
                // Print the filename
                std::cout << entry.path().filename().c_str() << std::endl;
            }
        } else 
        {
            std::cerr << "Directory not found or is not a directory." << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& ex)
    {
        std::cerr << "Filesystem error: " << ex.what() << std::endl;
    }

    return 0;
}
