//
// Created by andrei on 08.03.2021.
//
#pragma once

#include <options.hpp>

namespace bayan {

class file_dublicate_parser {
  file_dublicate_parser(opt_hash&& hash);

  vec_path scan_dublicate(const group_path& g_path);
};

}  // namespace bayan