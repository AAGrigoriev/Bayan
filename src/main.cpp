#include <filesystem>
#include <iostream>

#include "com_parser.hpp"

int main(int argc, char *argv[]) {
    
  bayan::command_parser parser{argc, argv};

  auto opt_parser = parser.parse_data();

  if (!opt_parser) {
    return 0;
  }

  std::cout << "I Have data\n";

  return 0;
}