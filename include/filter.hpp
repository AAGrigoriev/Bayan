#pragma once
#include <filesystem>

namespace bayan
{
    class filter_dir
    {
    public:
        bool is_valid_dir(fs::path const &path) { return true; }
        bool is_valid_file(fs::path const &path) { return true; }
    };

} // namespace bayan