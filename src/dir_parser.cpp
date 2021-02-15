#include "dir_parser.hpp"

namespace bayan
{
    dir_parser::dir_parser(opt_dir &dir) : opt(dir.scan_opt)
    {
        //customize filter_dir
    }

    dir_parser::dir_parser(opt_dir &&dir) : opt(std::move(dir.scan_opt))
    {
        //customize filter_dir
    }

    group_path dir_parser::scan_dir()
    {
        group_path out;
        for (auto &path : opt.includes_path)
        {
            fs::recursive_directory_iterator it{path, fs::directory_options::skip_permission_denied}, it_end{};

            for (fs::recursive_directory_iterator it{path, fs::directory_options::skip_permission_denied}, it_end{}; it != it_end; ++it)
            {
                if((*it).is_directory() && !filter.is_valid_dir((*it).path()))
                {
                    it.disable_recursion_pending();
                }
                else
                {
                    if((*it).is_regular_file() && !filter.is_valid_file((*it).path()))
                    {
                        
                    }
                }
            }
        }
    }

} // namespace bayan