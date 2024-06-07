#include "com_parser.hpp"
#include "dir_parser.hpp"
#include "file_dublicate_parser.hpp"

int main(int argc, char* argv[]) {
  bayan::command_parser parser{argc, argv};

  if (auto opt_parser = parser.parse_data()) {
    bayan::dir_parser dir_parser(std::move(opt_parser.value().dir_opt));
    auto result = dir_parser.get_group_path();
    bayan::file_dublicate_parser file_parser(
        std::move(opt_parser.value().hash_opt));
    const auto res = file_parser.scan_dublicate(result);
  }

  return 0;
}
