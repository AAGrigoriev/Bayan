#include "com_parser.hpp"
#include <exception>
#include <iostream>

namespace bayan
{
    command_parser::command_parser(int argc, char *argv[]) : _desc("options")
    {
        _desc.add_options()("include,i", bpo::value<std::vector<fs::path>>(), "Include path for scanning")("exclude,e", bpo::value<std::vector<fs::path>>(), "Exclude directory")("level,l", bpo::value<int>()->default_value(-1), "Maximum depth of scan, -1 no limit")("size,s", bpo::value<int>()->default_value(5), "Minimum file size in bytes")("mask,m", bpo::value<std::vector<std::string>>(), "Masks for filename")("block,b", bpo::value<int>()->default_value(10), "Block size in bytes")("hash,h", bpo::value<std::string>()->default_value("crc32"), "Hash algorithm")("help,h", "Help screen");

        bpo::store(bpo::parse_command_line(argc, argv, _desc), _mp);

        bpo::notify(_mp);
    }

    std::optional<opt_data> command_parser::parse_data()
    {
        try
        {
            if (_mp.count("help"))
            {
                std::cout << _desc;
                return std::nullopt;
            }

            opt_data out_data;

            if (_mp.count("include"))
            {
                auto &elem = _mp["include"].as<std::vector<fs::path>>();

                for (auto &path : elem)
                {
                    if (fs::exists(path))
                    {
                        if (path.is_relative())
                        {
                            std::error_code error;
                            fs::path temp_path = fs::canonical(path, error);
                            if (!error)
                            {
                                out_data.dir_opt.scan_opt.includes_path.push_back(temp_path);
                            }
                            else
                                std::cerr << error.message() << " on" << path;
                        }
                        else
                            out_data.dir_opt.scan_opt.includes_path.push_back(path);
                    }
                }
            }
            else
            {
                throw std::logic_error("empty include field");
            }
            if (_mp.count("exclude"))
            {
                auto &elem = _mp["exclude"].as<std::vector<fs::path>>();

                for (auto &path : elem)
                {
                    if (path.is_relative())
                    {
                        std::error_code error;
                        fs::path temp_path = fs::canonical(path, error);
                        if (!error)
                        {
                            out_data.dir_opt.filter_opt.exclude_path.push_back(temp_path);
                        }
                        else
                            std::cerr << error.message() << " on" << path;
                    }
                    else
                        out_data.dir_opt.filter_opt.exclude_path.push_back(path);
                }
            }

            if (_mp.count("level"))
            {
                out_data.dir_opt.scan_opt.level_scanning = _mp["level"].as<int>();
            }

            if (_mp.count("size"))
            {
                out_data.dir_opt.scan_opt.min_file_size = _mp["size"].as<int>();
            }

            if (_mp.count("mask"))
            {
                out_data.dir_opt.filter_opt.mask_to_file = std::move(_mp["mask"].as<std::vector<std::string>>());
            }

            if (_mp.count("block"))
            {
                out_data.hash_opt.block_size = _mp["block"].as<int>();
            }

            if (_mp.count("hash"))
            {
                std::string const &str = _mp["hash"].as<std::string>();
                if (str == "crc32")
                {
                    out_data.hash_opt.h_algo = hash_algo::crc_32;
                }
                else if (str == "md5")
                {
                    out_data.hash_opt.h_algo = hash_algo::md5;
                }
            }

            return out_data;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return std::nullopt;
        }
    }
} // namespace bayan