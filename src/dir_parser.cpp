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

    group_path dir_parser::get_group_path()
    {
        group_path out = scan_dir();
        delete_uniqe_path(out);
        return out;
    }

    group_path dir_parser::scan_dir()
    {
        group_path out;
        for (auto &path : opt.includes_path)
        {
            for (fs::recursive_directory_iterator it{path, fs::directory_options::skip_permission_denied}, it_end{}; it != it_end; ++it)
            {
                if (filter.approach_dir((*it).path()))
                {
                    it.disable_recursion_pending();
                }
                else
                {
                    fs::path const &temp_path = (*it).path();

                    if (filter.approach_file(temp_path))
                    {
                        out[fs::file_size(temp_path)].push_back(temp_path);
                    }
                }
            }
        }
    }

    group_path delete_uniqe_path(group_path &not_uniqe)
    {
        for (auto it = not_uniqe.begin(); it != not_uniqe.end();)
        {
            if (it->second.size() < 2)
            {
                it = not_uniqe.erase(it);
            }
            else
                ++it;
        }
    }

} // namespace bayan

