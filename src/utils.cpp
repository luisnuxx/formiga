//
// Created by Luis Rodrigues on 18/02/2018.
//

#include "utils.hpp"

// source
namespace luisnuxx
{
    std::string getWorkingDir()
    {
            fs::path path1(boost::dll::program_location());
            return path1.string();
    }
}
