//
// Created by Luis Rodrigues on 18/02/2018.
//
#include <first_include.hpp>
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

    std::string loadFileContent(std::string filename) {

        //Initialize the memory-mapped file
        mapped_file_source file(filename);
        //Read the entire file into a string
        std::string fileContent(file.data(), file.size());
        //Print the string
        //std::cout << fileContent;
        //Cleanup
        file.close();
        return fileContent;
    }


}
