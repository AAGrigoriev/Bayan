#pragma once
#include <filesystem>

namespace bayan
{
    class filter_dir
    {
    public:
        bool approach_dir(fs::path const &path) { return true; }
        bool approach_file(fs::path const &path) { return true; }
    };

} // namespace bayan