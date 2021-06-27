//
// Created by andrei on 22.02.2021.
//
#pragma once

#include <regex>
#include <string>

namespace bayan {

class mask {
 public:
  explicit mask(const std::string& sting_in);
  bool isValid(const std::string& to_match);

 private:
  void prepare(const std::string& prep);
  std::regex reg_;
};
}  // namespace bayan
