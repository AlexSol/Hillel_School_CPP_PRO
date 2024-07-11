// Реверсивне видалення папки std::filesystem


#include <filesystem>
#include <iostream>

void reverse_delete(const std::filesystem::path& dir) 
{
    for (auto it = std::filesystem::recursive_directory_iterator(dir); 
                it != std::filesystem::recursive_directory_iterator();
                ++it){
        try {
            if (std::filesystem::is_regular_file(*it)){
                std::filesystem::remove(*it);
                std::cout << "Deleted file: " << *it << std::endl;
            } else if (std::filesystem::is_directory(*it))
			{
                std::filesystem::remove(*it); // Remove empty directories
                std::cout << "Deleted directory: " << *it << std::endl;
            }
        } catch (const std::filesystem::filesystem_error& ex)
		{
            std::cerr << "Filesystem error: " << ex.what() << std::endl;
        }
    }
}

int main()
{
    std::string folder_path = "example_folder";

    try 
	{
        reverse_delete(folder_path);
    } catch (const std::filesystem::filesystem_error& ex)
	{
        std::cerr << "Filesystem error: " << ex.what() << std::endl;
    }
    return 0;
}

