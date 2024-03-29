#pragma once

#include <algorithm>
#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <fstream>
#include <string>

#include "options.hpp"

template <typename T>
T calc_check_sum(const char* buf, std::size_t size);

template <>
std::size_t calc_check_sum(const char* buf, std::size_t size) {
  boost::crc_32_type result;
  result.process_bytes(buf, size);
  return result.checksum();
}

using md5digest_t = std::array<unsigned int, 4>;

template <>
md5digest_t calc_check_sum(const char* buf, std::size_t size) {
  boost::uuids::detail::md5 hash;
  boost::uuids::detail::md5::md5::digest_type digest;
  hash.process_bytes(buf, size);
  hash.get_digest(digest);
  return {digest[0], digest[1], digest[2], digest[3]};
}

namespace bayan {

/*
  @brief Класс, хранящий хеши файла и позволяющий сравнивать файлы между собой
*/
template <typename T>
class file_wrapper {
  std::vector<T>::iterator type_it;

 public:
  file_wrapper(const fs::path& path, std::size_t file_size,
               std::size_t block_size)
      : name_(path), file_size_(file_size), block_size_(block_size) {}

  bool operator==(const file_wrapper<T>& other) {
    auto current_iter = hashes_.begin();
    auto other_iter = other.hashes_.begin();
    std::ifstream in_this;
    std::ifstream in_other;

    // Поскольку в file_comparator все файлы лежат отсортированные по размеру,
    // то this.hashes_.size() == other.hashes_.size()
    while (has_next_block(current_iter)) {
      if (next_block(current_iter, in_this) !=
          next_block(other_iter, in_other)) {
        return false;
      }
    }
    return true;
  }

   private:
    // Проверка наличия блоков для сравнения.
    bool has_next_block(type_it it) {
      return isComplite() || it != hashes_.end();
    }

    bool isComplite() { return hashes_.size() * block_size_ == file_size_; }

    T& next_block(type_it it, std::ifstream & stream) {
      if (it == hashes_.end() && !isComplite()) {
        char buffer[block_size_];
        std::fill(buffer, buffer + block_size_, 0);

        if (!stream.is_open()) {
          stream.open(name_, std::ios::binary);
        }

        stream.seekg(hashes_.size() * block_size_);
        stream.read(buffer, block_size_);
        hashes_.emplace_back(calc_check_sum(buffer, block_size_));
        return hashes_.back();
      }
      return *it++;
    }

    fs::path name_;           // путь до файла
    std::size_t file_size_;   // размер файла
    std::size_t block_size_;  // размер блока
    std::vector<T>
        hashes_;  // хеши блока в котором находится файл, либо мд5, либо crc32
  };

}  // namespace bayan