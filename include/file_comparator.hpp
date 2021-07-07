#pragma once

#include <algorithm>

#include "file_wrapper.hpp"

namespace bayan {

class IFile_comparator {
 public:
  virtual ~IFile_comparator() = default;
  virtual void add_paths(const group_path&) = 0;
  virtual const vec_path& duplicates() const = 0;
};

template <typename hash_algo>
class file_comparator : public IFile_comparator {
 public:
  file_comparator(std::size_t block_size) : block_size(block_size) {}

  void add_path(const group_path& size_paths) {
    for (const auto& param : size_paths) {
      v_file_wrapper.clear();
      for (const auto& path : param.second) {
        auto file_wrapper =
            file_wrapper<hash_algo>(path, fs::file_size(path), block_size);
        if (std::any_of(v_file_wrapper.begin(), v_file_wrapper.end(),
                        [&v_file_wrapper](const auto& wrapper) {
                          return v_file_wrapper == wrapper;
                        })) {
          v_file_wrapper.push_back(std::move(file_wrapper));
        } else {
          duplicates.push_back(path);
        }
      }
    }
  }

 private:
  std::size_t block_size_;
  std::vector<file_wrapper<hash_algo>> v_file_wrapper_;
  std::vector<std::string> duplicates_;
};

}  // namespace bayan