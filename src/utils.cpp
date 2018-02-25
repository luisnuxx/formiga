//
// Created by Luis Rodrigues on 18/02/2018.
//

#include "utils.hpp"

// source
namespace luisnuxx
{
    std::string getWorkingDir()
    {
        auto cwd = fs::current_path();
        //fs::path path1(boost::dll::program_location());
        return cwd.string();
    }
}
