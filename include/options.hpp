#pragma once

#include <boost/program_options.hpp>
#include <filesystem>
#include <string>
#include <vector>

namespace bayan {

namespace bpo = boost::program_options;
namespace fs = std::filesystem;
using group_path = std::unordered_map<int, std::vector<fs::path>>;
using vec_path = std::vector<fs::path>;

enum class hash_algo { crc_16 = 0, crc_32 };

struct opt_filter {
  std::vector<fs::path> exclude_path;
  std::vector<std::string> mask_to_file;
  int min_file_size;
};

struct opt_scan {
  std::vector<fs::path> includes_path;
  int level_scanning;
};

struct opt_dir {
  opt_filter filter_opt;
  opt_scan scan_opt;
};

struct opt_hash {
  std::size_t block_size;
  hash_algo h_algo;
};

struct opt_data {
  opt_hash hash_opt;
  opt_dir dir_opt;
};

}  // namespace bayan