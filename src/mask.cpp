//
// Created by andrei on 22.02.2021.
//

#include "mask.hpp"

#include <algorithm>

namespace bayan {

mask::mask(std::string string_in)
    : reg_(prepare(string_in), std::regex::icase) {}

std::string mask::prepare(std::string prep) {
  if (const auto pos = prep.find('*'); pos != std::string::npos) {
    prep.erase(pos, 1);
  }
  if (const auto pos = prep.find('.'); pos != std::string::npos) {
    prep.erase(pos, 1);
  }
  return prep;
}

bool mask::isValid(const std::string& to_match) {
  return std::regex_search(to_match, reg_);
}

}  // namespace bayan
