#include "com_parser.hpp"
#include <iostream>
#include <filesystem>

int main(int argc, char *argv[])
{
    // bayan::command_parser parser{argc, argv};

    // auto opt_parser = parser.parse_data();

    // if (!opt_parser)
    // {
    //     return 0;
    // }

    // std::cout << "I Have data\n";

    namespace fs = std::filesystem;

    for (auto i = fs::recursive_directory_iterator("CMakeFiles");
         i != fs::recursive_directory_iterator();
         ++i)
    {
        std::cout << std::string(i.depth() * 2, ' ') << *i << " depth = " << i.depth();
        if (fs::is_symlink(i->symlink_status()))
            std::cout << " -> " << fs::read_symlink(*i);
        std::cout << '\n';

        // do not descend into "b"
        if (i->path().filename() == "ssss")
        {
            std::cout << "IM here " << i->path().filename() << std::endl;
            i.disable_recursion_pending();
        }
    }

    return 0;
}