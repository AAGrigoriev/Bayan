#pragma once

#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
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
 public:
  file_wrapper(const fs::path& path, std::size_t file_size,
               std::size_t block_size)
      : name_(path), file_size_(file_size), block_size_(block_size) {}

  bool operator==(const file_wrapper<T>& other) {}

 private:
  fs::path name_;           // путь до файла
  std::size_t file_size_;   // размер файла
  std::size_t block_size_;  // размер блока
  std::vector<T>
      hashes_;  // хеши блока в котором находится файл, либо мд5, либо crc32
};

}  // namespace bayan