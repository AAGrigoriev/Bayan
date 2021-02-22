//
// Created by andrei on 22.02.2021.
#include "filter.hpp"
#include <regex>

namespace bayan
{
    filter_dir::filter_dir(opt_filter&& opt_filter):filter_opt(opt_filter) {


    }

    bool filter_dir::approach_dir(fs::path const &path){
        return std::any_of(filter_opt.exclude_path.begin(),filter_opt.exclude_path.end(),
                            [&path](fs::path& filter_path)
                            {
                                return path == filter_path;
                            }
                            );
    }

    bool filter_dir::approach_file(const fs::path &path) {

        if(fs::is_regular_file(path) &&
           fs::file_size(path) >= filter_opt.min_file_size )
        {


        }





    }
}





