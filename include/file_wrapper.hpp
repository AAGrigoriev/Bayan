#pragma once

#include <options.hpp>
#include <string>
#include <vector>

namespace bayan {
/*
  @brief Класс, хранящий хеши файла и позволяющий сравнивать файлы между собой
*/
template <typename T>
class file_comparator {
 public:
  file_comparator(const fs::path& path, std::size_t file_size,
                  std::size_t block_size)
      : name(path), file_size(file_size), block_size(block_size) {}

 
  bool operator==(const file_comparator<T>& other) {
    
  }

 private:
  std::string name;        // путь до файла
  std::size_t file_size;   // размер файла
  std::size_t block_size;  // размер блока
  std::vector<T> hashes;   // хеши блока в котором находится файл, либо мд5, либо crc32
};

}  // namespace bayan