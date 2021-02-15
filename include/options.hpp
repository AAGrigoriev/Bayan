#pragma once

#include <boost/program_options.hpp>
#include <filesystem>
#include <vector>
#include <string>

namespace bayan
{
    namespace bpo        = boost::program_options;
    namespace fs         = std::filesystem;
    using group_path     = std::unordered_map<int,std::vector<fs::path>>;

    enum class hash_algo
    {
        crc_32 = 0,
        md5
    };

    struct opt_filter
    {
        std::vector<fs::path> exclude_path;
        std::vector<std::string> mask_to_file;
    };
    struct opt_scan
    {
        std::vector<fs::path> includes_path;
        int level_scanning;
        int min_file_size;
    };

    struct opt_dir
    {
        opt_filter  filter_opt;
        opt_scan    scan_opt;
    };

    struct opt_hash
    {
        long block_size;
        hash_algo h_algo;
    };

    struct opt_data
    {
        opt_hash hash_opt;
        opt_dir dir_opt;
    };

} // namespace bayan