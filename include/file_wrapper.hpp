#pragma once

#include "options.hpp"
#include <string>
#include <vector>

namespace bayan {
/*
  @brief Класс, хранящий хеши файла и позволяющий сравнивать файлы между собой
*/
template <typename T>
class file_wrapper {
 public:
  file_wrapper(const fs::path& path, std::size_t file_size,
                  std::size_t block_size)
      : name_(path), file_size_(file_size), block_size_(block_size) {}

  bool operator==(const file_wrapper<T>& other) {}

 private:
  fs::path name_;           // путь до файла
  std::size_t file_size_;   // размер файла
  std::size_t block_size_;  // размер блока
  std::vector<T> hashes_;  // хеши блока в котором находится файл, либо мд5, либо crc32
};

}  // namespace bayan