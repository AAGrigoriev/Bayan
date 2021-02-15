#pragma once

#include "options.hpp"
#include <optional>
#include <boost/program_options.hpp>

namespace bayan
{
    class command_parser
    {
    public:
        command_parser(int argc, char *argv[]);

        std::optional<opt_data> parse_data();
        
    private:
        bpo::variables_map _mp;
        bpo::options_description _desc;
    };

} // namespace bayan
