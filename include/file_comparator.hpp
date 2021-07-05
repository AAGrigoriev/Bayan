#pragma once

#include "file_wrapper.hpp"

namespace bayan {

class IFile_comparator {
 public:
  virtual ~IFile_comparator() = default;
  virtual void add_paths(const vec_path&) = 0;
  virtual const vec_path& duplicates() const = 0;
};

template <typename hash_algo>
class file_comparator : public IFile_comparator {
 public:
  file_comparator(std::size_t block_size) {}

 private:
  std::vector<file_wrapper<hash_algo>> v_file_wrapper;
};

}  // namespace bayan