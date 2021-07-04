#pragma once

#include <options.hpp>
#include <unordered_map>

#include "filter.hpp"

namespace bayan {

class dir_parser {
 public:
  dir_parser(opt_dir&& opt);

  group_path get_group_path();

 private:
  group_path scan_dir();
  void delete_uniqe_path(group_path& not_uniqe);

  filter_dir filter_;
  opt_scan opt_;
};

}  // namespace bayan