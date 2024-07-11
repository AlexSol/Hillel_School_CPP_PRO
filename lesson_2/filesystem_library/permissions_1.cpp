// std::filesystem - дозволи

#include <iostream>
#include <filesystem>

int main() {
    std::filesystem::path file_path = "example.txt";
    if (std::filesystem::exists(file_path))
    {
        std::filesystem::permissions(file_path, std::filesystem::perms::owner_write, std::filesystem::perm_options::add);
        std::cout << "File permissions changed successfully." << std::endl;
    } 
    return 0;
}
