//
// Created by andrei on 22.02.2021.
//

#include "mask.hpp"
#include <algorithm>
namespace bayan
{
    mask::mask(std::string& string_in)
    {
        prepare(string_in);
        reg.assign(string_in);
    }

    void mask::prepare(std::string& prep)
    {
        prep.erase(std::find(prep.begin(),prep.end(),'*'));
        prep.erase(std::find(prep.begin(),prep.end(),'.'));
    }

    bool mask::isValid(const std::string& to_match){
        return std::regex_match(to_match,reg);
    }

}


