// Видалення файлу std::filesystem

#include <filesystem>
#include <iostream>

int main()
{
    std::string file_path = "example.txt";

    try
	{
        // Delete the file
        const auto is_remove = std::filesystem::remove(file_path);

        const std::string message = is_remove ? file_path + " file was deleted" : file_path + " file not exist";
        std::cout << message << std::endl;

        std::cout << "File deleted successfully." << std::endl;
    } catch (const std::filesystem::filesystem_error& ex)
	{
        std::cerr << "Filesystem error: " << ex.what() << std::endl;
    }
    return 0;
}




