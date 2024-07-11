#include <iostream>
#include <filesystem>

bool copy_directory(const std::filesystem::path& source, const std::filesystem::path& destination)
{
    try
    {
        // Create the destination directory
        if (!std::filesystem::create_directory(destination))
        {
            std::cerr << "Failed to create destination directory." << std::endl;
            return false;
        }

        // Recursively copy directory contents
        for (const auto& entry : std::filesystem::recursive_directory_iterator(source))
        {
            std::filesystem::copy(entry, destination / entry.path().filename(), std::filesystem::copy_options::recursive);
        }
        return true;
    } catch (const std::filesystem::filesystem_error& ex)
    {
        std::cerr << "Filesystem error: " << ex.what() << std::endl;
        return false;
    }
}

int main()
{
    std::filesystem::path source_dir = "source_directory";
    std::filesystem::path destination_dir = "destination_directory";

    if (copy_directory(source_dir, destination_dir))
    {
        std::cout << "Directory copied successfully." << std::endl;
    } else
    {
        std::cerr << "Failed to copy directory." << std::endl;
    }

    return 0;
}