#pragma once
#include <options.hpp>
#include <unordered_map>
#include "filter.hpp"

namespace bayan
{
    class dir_parser
    {
    public:
        dir_parser(opt_dir &opt);
        dir_parser(opt_dir &&opt);

        group_path scan_dir();

    private:
        filter_dir filter;
        opt_scan opt;
    };

} // namespace bayan