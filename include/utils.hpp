//
// Created by Luis Rodrigues on 18/02/2018.
//

#ifndef FORMIGA_UTILS_H
#define FORMIGA_UTILS_H
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

namespace fs = boost::filesystem;
using namespace boost::iostreams;

// header
namespace luisnuxx
{
    std::string getWorkingDir() ;
    std::string loadFileContent(std::string filename);
}


#endif //FORMIGA_UTILS_H
