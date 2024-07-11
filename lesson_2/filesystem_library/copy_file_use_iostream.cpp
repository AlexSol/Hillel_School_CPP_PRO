// Копіювання файлу через потоки

#include <iostream>
#include <fstream>

int main()
{
    const char* source_file = "source_file.txt";
    const char* target_file = "target_file.txt";

    std::ifstream source(source_file, std::ios::binary);
    if (!source.is_open())
    {
        std::cerr << "Failed to open source file." << std::endl;
        return 1;
    }

    std::ofstream target(target_file, std::ios::binary);
    if (!target.is_open())
	{
        std::cerr << "Failed to open target file." << std::endl;
        source.close();
        return 1;
    }
}