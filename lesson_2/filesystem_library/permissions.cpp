// std::filesystem - дозволи

#include <iostream>
#include <filesystem>

int main()
{
    std::filesystem::path file_path = "remove_file_filesystem";
    if (std::filesystem::exists(file_path))
    {
        std::filesystem::permissions(file_path, std::filesystem::perms::none, std::filesystem::perm_options::add);
        std::cout << "File permissions changed successfully." << std::endl;
    }
    else
    {
        std::cerr << "File does not exist." << std::endl;
    }
    return 0;
}
