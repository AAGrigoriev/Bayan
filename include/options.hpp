#include <boost/program_options.hpp>
#include <filesystem>
#include <vector>
#include <string>


namespace bayan
{
    namespace bpo = boost::program_options;
    namespace fs = std::filesystem;

    enum class hash_algo
    {
        crc_32 = 0,
        md5
    };

    struct opt_dir
    {
        std::vector<fs::path>       includes_path;
        std::vector<fs::path>       exclude_path;
        int                         level_scanning;
        int                         min_file_size;
        std::vector<std::string>    mask_to_file;
    };

    struct opt_hash
    {
        long                        block_size;
        hash_algo                   h_algo;

    };

    struct opt_data
    {
        opt_dir  dir_opt;
        opt_hash hash_opt;
    };

} // namespace bayan